/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.util.Log;
import android.widget.Toast;

import com.easyndk.classes.AndroidNDKHelper;
import com.easyndk.classes.NDKMessage;
import com.google.android.gms.auth.api.Auth;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.auth.api.signin.GoogleSignInResult;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.common.api.Status;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthCredential;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.auth.GoogleAuthProvider;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.lasertoast.lorafel.R;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public class AppActivity extends Cocos2dxActivity implements
        GoogleApiClient.OnConnectionFailedListener
{

    private GoogleApiClient mGoogleApiClient;
    private static final int RC_SIGN_IN = 9001;
    private FirebaseAuth mAuth;
    private FirebaseAuth.AuthStateListener mAuthListener;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        AndroidNDKHelper.SetNDKReceiver(this);
        mAuth = FirebaseAuth.getInstance();

        GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
                .requestIdToken(getString(R.string.default_web_client_id))
                .requestEmail()
                .build();

        mGoogleApiClient = new GoogleApiClient.Builder(this)
                .enableAutoManage(this /* FragmentActivity */, this /* OnConnectionFailedListener */)
                .addApi(Auth.GOOGLE_SIGN_IN_API, gso)
                .build();

        mAuthListener = new FirebaseAuth.AuthStateListener() {
            @Override
            public void onAuthStateChanged(@NonNull FirebaseAuth firebaseAuth) {
                FirebaseUser user = firebaseAuth.getCurrentUser();
                if (user != null) {
                    // User is signed in
                    Log.d(TAG, "onAuthStateChanged:signed_in:" + user.getUid());
                    setCppAuthState("LoggedInState");
                    loadUserDataFromDatabase();
                } else {
                    // User is signed out
                    Log.d(TAG, "onAuthStateChanged:signed_out");
                    setCppAuthState("AuthenticationFailedState");
                }
            }
        };

    }

    private void loadUserDataFromDatabase() {
        FirebaseUser user = FirebaseAuth.getInstance().getCurrentUser();
        DatabaseReference mDatabase = FirebaseDatabase.getInstance().getReference();
        final String userId = user.getUid();
        mDatabase.child("users").child(userId).addListenerForSingleValueEvent(
                new ValueEventListener() {
                    @Override
                    public void onDataChange(DataSnapshot dataSnapshot) {
                        Map<String, Object> user =((Map<String, Object>)dataSnapshot.getValue());
                        Log.w(TAG, "getUser:got user");
                        JSONObject paramList = new JSONObject();
                        try {
                            paramList.put(userId,user);
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
//                        Map<String, Object> items = (Map<String, Object>) user.get("items");
//                        Map<String, Object> equipSlots = (Map<String, Object>) user.get("equip_slots");
//
//                        Iterator it = items.entrySet().iterator();
//                        while (it.hasNext()) {
//                            Map.Entry pair = (Map.Entry)it.next();
//                            try {
//                                paramList.put(pair.getKey().toString(), pair.getValue());
//                            } catch (JSONException e) {
//                                e.printStackTrace();
//                            }
//                            it.remove(); // avoids a ConcurrentModificationException
//                        }
//                        try {
//                            paramList.put("items", items);
//                        } catch (JSONException e) {
//                            e.printStackTrace();
//                        }
//
//                        try {
//                            paramList.put("equip_slots", equipSlots);
//                        } catch (JSONException e) {
//                            e.printStackTrace();
//                        }

                        AndroidNDKHelper.SendMessageWithParameters("onCompleteUserQuery", paramList);
                    }

                    @Override
                    public void onCancelled(DatabaseError databaseError) {
                        Log.w(TAG, "getUser:onCancelled", databaseError.toException());
                    }
                });

    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        Log.d(TAG, "onActivityResult(): requestCode=" + requestCode);
        super.onActivityResult(requestCode, resultCode, data);

        // Result returned from launching the Intent from GoogleSignInApi.getSignInIntent(...);
        if (requestCode == RC_SIGN_IN) {
            GoogleSignInResult result = Auth.GoogleSignInApi.getSignInResultFromIntent(data);
            handleSignInResult(result);
        }
    }

    private void handleSignInResult(GoogleSignInResult result) {
        Log.d(TAG, "handleSignInResult:" + result.isSuccess());
        if (result.isSuccess()) {
            GoogleSignInAccount acct = result.getSignInAccount();
            firebaseAuthWithGoogle(acct);
            Log.d(TAG, "handleSignInResult(): Signed In");
        } else {
            Log.d(TAG, "handleSignInResult(): Signed Out");
        }
    }

    private void signIn() {
        Intent signInIntent = Auth.GoogleSignInApi.getSignInIntent(mGoogleApiClient);
        startActivityForResult(signInIntent, RC_SIGN_IN);
        setCppAuthState("AuthenticatingState");
    }

    private void signOut() {
        Auth.GoogleSignInApi.signOut(mGoogleApiClient).setResultCallback(
                new ResultCallback<Status>() {
                    @Override
                    public void onResult(@NonNull Status status) {
                        Log.d(TAG, "Done signOut()");
                    }
                });
    }

//    private void revokeAccess() {
//        Auth.GoogleSignInApi.revokeAccess(mGoogleApiClient).setResultCallback(
//                new ResultCallback<Status>() {
//                    @Override
//                    public void onResult(@NonNull Status status) {
//                        Log.d(TAG, "Done revokeAccess()");
//                        setCppAuthState("AuthenticationFailedState");
//                    }
//                });
//    }

    @Override
    public void onConnectionFailed(@NonNull ConnectionResult connectionResult) {
        Log.d(TAG, "onConnectionFailed:" + connectionResult);
        setCppAuthState("AuthenticationFailedState");
    }

    protected void setCppAuthState(String state) {
        JSONObject message = new JSONObject();
        try {
            message.put("state", state);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        AndroidNDKHelper.SendMessageWithParameters("changeStateSelector", message);

    }

    public void signIn(JSONObject parameters) {
        this.signIn();
    }

    @Override
    public void onStart() {
        super.onStart();
        mAuth.addAuthStateListener(mAuthListener);
    }

    @Override
    public void onStop() {
        super.onStop();
        if (mAuthListener != null) {
            mAuth.removeAuthStateListener(mAuthListener);
        }
    }

    private void firebaseAuthWithGoogle(GoogleSignInAccount acct) {
        Log.d(TAG, "firebaseAuthWithGoogle:" + acct.getId());

        AuthCredential credential = GoogleAuthProvider.getCredential(acct.getIdToken(), null);
        mAuth.signInWithCredential(credential)
                .addOnCompleteListener(this, new OnCompleteListener<AuthResult>() {
                    @Override
                    public void onComplete(@NonNull Task<AuthResult> task) {
                        Log.d(TAG, "signInWithCredential:onComplete:" + task.isSuccessful());

                        if (!task.isSuccessful()) {
                            Log.w(TAG, "signInWithCredential", task.getException());
                        }
                    }
                });
    }
}

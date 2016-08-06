//
// Created by Jarad DeLorenzo on 8/6/16.
//

#include "GpgStateManager.h"

using namespace lorafel;

bool GpgStateManager::is_auth_in_progress_ = false;
std::unique_ptr<gpg::GameServices> GpgStateManager::game_services_;

gpg::GameServices *GpgStateManager::GetGameServices() {
    return game_services_.get();
}

void GpgStateManager::BeginUserInitiatedSignIn() {
    if (!game_services_->IsAuthorized()) {
        CCLOG("StartAuthorizationUI");
        game_services_->StartAuthorizationUI();
    }
}

void GpgStateManager::SignOut() {
    if (game_services_->IsAuthorized()) {
        CCLOG("SignOut");
        game_services_->SignOut();
    }
}

void GpgStateManager::UnlockAchievement(char const *achievement_id) {
    if (game_services_->IsAuthorized()) {
        CCLOG("Achievement unlocked");
        game_services_->Achievements().Unlock(achievement_id);
    }
}

void GpgStateManager::SubmitHighScore(char const *leaderboard_id, uint64_t score) {
    if (game_services_->IsAuthorized()) {
        CCLOG("High score submitted");
        game_services_->Leaderboards().SubmitScore(leaderboard_id, score);
    }
}

void GpgStateManager::ShowAchievements() {
    if (game_services_->IsAuthorized()) {
        CCLOG("Show achievements");
        game_services_->Achievements().ShowAllUI([](gpg::UIStatus const &status) {
            if (gpg::IsSuccess(status)) {
                CCLOG("Achievements Result: success.");
            } else {
                CCLOG("Achievements Result: failure.");
            }
        });
    }
}

void GpgStateManager::ShowLeaderboards() {
    if (game_services_->IsAuthorized()) {
        CCLOG("Show leaderboards");
        game_services_->Leaderboards().ShowAllUI([](gpg::UIStatus const &status) {
            if (gpg::IsSuccess(status)) {
                CCLOG("Leaderboards Result: success.");
            } else {
                CCLOG("Leaderboards Result: failure.");
            }
        });
    }
}

void GpgStateManager::InitServices(gpg::PlatformConfiguration* config) {

    auto started_callback = [&](gpg::AuthOperation op) {
        CCLOG("Birdfuck");
    };

    auto finished_callback = [&](gpg::AuthOperation op, gpg::AuthStatus status) {
        if(gpg::IsSuccess(status)) {
            CCLOG("Yay! Logged in");
        } else {
            CCLOG("=( Not logged in");
            BeginUserInitiatedSignIn();
        }
    };

    CCLOG("Initializing Services");
    if (!game_services_) {
        CCLOG("Uninitialized services, so creating");
        game_services_ = gpg::GameServices::Builder()
                .SetOnAuthActionStarted([started_callback](gpg::AuthOperation op) {
                    is_auth_in_progress_ = true;
                    started_callback(op);
                })
                .SetOnAuthActionFinished([finished_callback](gpg::AuthOperation op,
                        gpg::AuthStatus status) {
                    CCLOG("Sign in finished with a result of %d", status);
                    is_auth_in_progress_ = false;
                    finished_callback(op, status);
                })
                .Create(*config);
    }
    CCLOG("Created");
}

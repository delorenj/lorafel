//
// Created by Jarad DeLorenzo on 8/22/16.
//

#ifndef LORAFEL_FIREBASEDATABASE_H
#define LORAFEL_FIREBASEDATABASE_H

namespace lorafel {
	class FirebaseDatabase : public cocos2d::Node {
	public:
		bool init() override;
		CREATE_FUNC(FirebaseDatabase);

		static FirebaseDatabase* getInstance() {
			if (_instance == nullptr) {
				_instance = FirebaseDatabase::create();
			}
			return _instance;
		}

	protected:
		void onCompleteUserQuery(cocos2d::Node* sender, cocos2d::Value data);
		static FirebaseDatabase* _instance;

	};
}

#endif //LORAFEL_FIREBASEDATABASE_H

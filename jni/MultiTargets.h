





#ifdef __cplusplus
extern "C"
{
#endif


	JNIEXPORT jint JNICALL
	JNI_OnLoad(JavaVM* vm, void* nReserved);

	JNIEXPORT void JNICALL
	Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_onQCARInitializedNative(JNIEnv* env, jobject);

	JNIEXPORT void JNICALL
	Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_initNativeCallback(JNIEnv* env, jobject obj);
/*
	JNIEXPORT void JNICALL
	Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_renderFrame(JNIEnv*, jobject);

	JNIEXPORT void JNICALL
	Java_com_qualcomm_QCARSamples_MultiTargets_MultiTargets_nativeTouchEvent(JNIEnv*, jobject, jint actionType, jint pointerId, jfloat x, jfloat y);

	JNIEXPORT void JNICALL
	Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeStart(JNIEnv*, jobject);

	JNIEXPORT void JNICALL
	Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeReset(JNIEnv*, jobject);

	JNIEXPORT void JNICALL
	Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeClear(JNIEnv*, jobject);

	JNIEXPORT void JNICALL
	Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeDelete(JNIEnv*, jobject);*/

	JNIEXPORT void JNICALL
	Java_com_qualcomm_QCARSamples_MultiTargets_GUIManager_nativeFood(JNIEnv*, jobject);

#ifdef __cplusplus
}
#endif

void showFeedButton();
void hideFeedButton();
void displayMessage(char* message);



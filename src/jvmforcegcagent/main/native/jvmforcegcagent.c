#include <stdlib.h>
#include <jvmti.h>

//
static jvmtiEnv *jvmtiiface;

#ifdef __cplusplus
	extern "C" {
#endif

//
JNIEXPORT void JNICALL
Java_name_ltp_jvmforcegcagent_JvmForceGcAgent_forceGc(JNIEnv *env, jobject thiz)
{
	if(jvmtiiface != NULL)
		(*jvmtiiface)->ForceGarbageCollection(jvmtiiface);
}

//
JNIEXPORT jboolean JNICALL
Java_name_ltp_jvmforcegcagent_JvmForceGcAgent_agentInitialized(JNIEnv *env, jobject thiz)
{
	return jvmtiiface != NULL;
}

//
JNIEXPORT jint JNICALL
Agent_OnLoad(JavaVM * jvm, char *options, void *reserved)
{	
	jint returnCode = (*jvm)->GetEnv(jvm, (void **)&jvmtiiface, JVMTI_VERSION_1_0);

	if(returnCode != JNI_OK)
	{
		fprintf(stderr, "JvmForceGcAgent: The version of JVMTI requested (1.0) is not supported by this JVM.\n");
		fflush(stderr);

		return JVMTI_ERROR_UNSUPPORTED_VERSION;
	}

	if(jvmtiiface != NULL)
		fprintf(stdout, "JvmForceGcAgent initialized.\n");
	else
		fprintf(stderr, "JvmForceGcAgent failed to initialize.\n");

	fflush(stdout);
	fflush(stderr);

	return JVMTI_ERROR_NONE;
}

#ifdef __cplusplus
	}
#endif


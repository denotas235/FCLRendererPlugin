#include <jni.h>
#include <stdio.h>
#include <EGL/egl.h>
#include <android/log.h>

#define LOG_TAG "MaliPlugin"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

JNIEXPORT jstring JNICALL
Java_com_mio_plugin_renderer_native_PluginNative_getGLExtensions(JNIEnv *env, jclass clazz) {
    EGLDisplay display = eglGetCurrentDisplay();
    const char *exts = NULL;
    if (display != EGL_NO_DISPLAY) exts = eglQueryString(display, EGL_EXTENSIONS);
    return (*env)->NewStringUTF(env, exts ? exts : "");
}

JNIEXPORT jfloat JNICALL
Java_com_mio_plugin_renderer_native_PluginNative_getGPUTemperature(JNIEnv *env, jclass clazz) {
    FILE *fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (!fp) return -1.0f;
    float temp; fscanf(fp, "%f", &temp); fclose(fp);
    return temp / 1000.0f;
}

JNIEXPORT jfloat JNICALL
Java_com_mio_plugin_renderer_native_PluginNative_getGPUFrequency(JNIEnv *env, jclass clazz) {
    FILE *fp = fopen("/sys/class/kgsl/kgsl-3d0/gpuclk", "r");
    if (!fp) return -1.0f;
    unsigned long freq; fscanf(fp, "%lu", &freq); fclose(fp);
    return freq / 1000000.0f;
}

JNIEXPORT jfloat JNICALL
Java_com_mio_plugin_renderer_native_PluginNative_getVRAMUsage(JNIEnv *env, jclass clazz) {
    FILE *fp = fopen("/sys/class/kgsl/kgsl-3d0/mem_used", "r");
    if (!fp) return -1.0f;
    unsigned long mem; fscanf(fp, "%lu", &mem); fclose(fp);
    return mem / (1024.0f * 1024.0f);
}

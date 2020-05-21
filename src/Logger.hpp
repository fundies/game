#ifndef LOGGER_HPP
#define LOGGER_HPP

#ifdef __ANDROID__
  #include <android/log.h>
  #define PrintMessage(...) __android_log_print(ANDROID_LOG_DEBUG, "GAYM", __VA_ARGS__)
#else
  #include <stdio.h>
  #define PrintMessage(...) printf(__VA_ARGS__); printf("\n")
#endif

#endif

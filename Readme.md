By default, JVM does not specify a way to perform a full garbage collection by a user request. You may know about [java.lang.System.gc()](http://docs.oracle.com/javase/8/docs/api/java/lang/System.html#gc--), but then you must already know that this function only suggests to the JVM to run garbage collection.

Fortunately there is [ForceGarbageCollection()](http://docs.oracle.com/javase/8/docs/platform/jvmti/jvmti.html#ForceGarbageCollection) defined in JVM Tool Interface (JVMTI) spec. And that's what this library here is all about.

## Building
You can just grab precompiled binaries from `out/` in this repo.

But building everything by yourself is easy, too.  
Open your shell and `cd` into this repo directory.

### Java
```
javac -source 1.5 -target 1.5 src/jvmforcegcagent/main/java/name/ltp/jvmforcegcagent/JvmForceGcAgent.java && cd src/jvmforcegcagent/main/java && jar cvf ../../../../out/jvmforcegcagent.jar name/ltp/jvmforcegcagent/JvmForceGcAgent.class && rm name/ltp/jvmforcegcagent/JvmForceGcAgent.class && cd ../../../../
```

### Windows x86
```
gcc -shared -Wall -D_JNI_IMPLEMENTATION_ -Wl,--kill-at -I"%JAVA_HOME%/include" -I"%JAVA_HOME%/include/win32"^
 -o out/jvmforcegcagent-win32.dll^
 src/jvmforcegcagent/main/native/jvmforcegcagent.c^
 && strip out/jvmforcegcagent-win32.dll
```

### Windows x86-64
```
gcc -shared -Wall -D_JNI_IMPLEMENTATION_ -Wl,--kill-at -I"%JAVA_HOME%/include" -I"%JAVA_HOME%/include/win32"^
 -o out/jvmforcegcagent-win64.dll^
 src/jvmforcegcagent/main/native/jvmforcegcagent.c^
 && strip out/jvmforcegcagent-win64.dll
```

### Linux x86-64
```
cc -shared -Wall -fpic -I$JAVA_HOME/include/ -I$JAVA_HOME/include/linux/ \
 -o out/libjvmforcegcagent-tux64.so \
 src/jvmforcegcagent/main/native/jvmforcegcagent.c \
 && strip out/libjvmforcegcagent-tux64.so
```

## Running
### Windows x86
```
 java -agentpath:jvmforcegcagent/out/jvmforcegcagent-win32.dll -Djava.library.path=jvmforcegcagent/out/ -cp jvmforcegcagent/out/* com.example.YourApp
```

### Windows x86-64
```
 java -agentpath:jvmforcegcagent/out/jvmforcegcagent-win64.dll -Djava.library.path=jvmforcegcagent/out/ -cp jvmforcegcagent/out/* com.example.YourApp
```

### Linux x86-64
```
 java -agentpath:jvmforcegcagent/out/libjvmforcegcagent-tux64.so -Djava.library.path=jvmforcegcagent/out/ -cp jvmforcegcagent/out/* com.example.YourApp
```

## Usage
```
if(name.ltp.jvmforcegcagent.JvmForceGcAgent.i() != null)
	name.ltp.jvmforcegcagent.JvmForceGcAgent.i().forceGc();
```

## License
Licensed under the CC0 1.0: http://creativecommons.org/publicdomain/zero/1.0/


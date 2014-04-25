package name.ltp.jvmforcegcagent;

public class JvmForceGcAgent
{
	//
	public static JvmForceGcAgent i()
	{
		return nativeLoaded && agentInitialized() ? i : null;
	}

	public native void forceGc();
	////


	//
	static final JvmForceGcAgent i = new JvmForceGcAgent();

	static volatile boolean nativeLoaded;

	static native boolean agentInitialized();

	static
	{
		String os = System.getProperty("os.name");
		if(os.contains("windows") || os.contains("Windows"))
			os = "win";
		if(os.contains("linux"))
			os = "tux";

		try
		{
			System.loadLibrary("jvmforcegcagent-" + os + System.getProperty("sun.arch.data.model"));

			nativeLoaded = true;
		}
		catch(UnsatisfiedLinkError ignored) {}
	}
	////
}


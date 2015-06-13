// Some copyright should be here...

using System.IO;
using UnrealBuildTool;

public class WebSocketCpp : ModuleRules
{
    public WebSocketCpp(TargetInfo Target)
    {

        PublicIncludePaths.AddRange(
            new string[] {
				"WebSocketCpp/Public"
				
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
				"WebSocketCpp/Private",
				
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
			{
				"Core",
                "WebSocketsClient"

				// ... add other public dependencies that you statically link with here ...
			}
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
			{
				"Slate", "SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
			{
				
				// ... add any modules that your module loads dynamically here ...
			}
            );
    }
}

/*
    // convenience Properties: Path to libraries
    private string ModulePath
    {
        get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty")); }
    }

    public bool LoadEasyWSClient(TargetInfo Target)
    {
        bool isLibrarySupported = false;

        if((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;
        }

        if (isLibrarySupported)
        {
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "easywsclient", "include"));
        }

        Definitions.Add(string.Format("WITH_EASYWSCLIENT_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }
}
    */
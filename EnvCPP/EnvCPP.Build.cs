// Copyright Epic Games, Inc. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class EnvCPP : ModuleRules
{
	private string ModulePath
	{
		get { return ModuleDirectory; }
	}

	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/")); }
	}

	public EnvCPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivateIncludePaths.Add("C:/Program Files/Epic Games/UE_4.26/Engine/Source/Runtime/Launch/Public/");

        LoadMosquitto(Target);
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}

    public bool LoadMosquitto(ReadOnlyTargetRules Target)
    {
       
        bool isLibrarySupported = false;

        string MosquittoPath = Path.Combine(ThirdPartyPath, "Mosquitto");

        string LibPath = "";
        bool isdebug = Target.Configuration == UnrealTargetConfiguration.Debug;

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LibPath = Path.Combine(MosquittoPath, "Libraries", "Win64");
            isLibrarySupported = true;
        }
        else
        {
            string Err = string.Format("{0} dedicated server is made to depend on {1}. We want to avoid this, please correct module dependencies.", Target.Platform.ToString(), this.ToString()); System.Console.WriteLine(Err);
        }

        if (isLibrarySupported)
        {
            //Add Include path 
            PublicIncludePaths.AddRange(new string[] { Path.Combine(MosquittoPath, "Includes") });

            // Add Library Path 
            PublicLibraryPaths.Add(LibPath);

            //Add Static Libraries
            PublicAdditionalLibraries.Add("mosquitto.lib");
            PublicAdditionalLibraries.Add("mosquittopp.lib");

            //Add Dynamic Libraries
            PublicDelayLoadDLLs.Add("mosquitto.dll");
            PublicDelayLoadDLLs.Add("mosquittopp.dll");
        }

        PublicDefinitions.Add(string.Format("WITH_MOSQUITTO_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }
}

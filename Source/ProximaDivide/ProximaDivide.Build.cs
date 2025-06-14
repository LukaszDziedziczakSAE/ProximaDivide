// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProximaDivide : ModuleRules
{
	public ProximaDivide(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Niagara", "AkAudio", "SlateCore", "LevelSequence", "OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemSteam" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "MovieScene" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

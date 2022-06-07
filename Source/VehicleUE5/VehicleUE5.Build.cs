// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VehicleUE5 : ModuleRules
{
	public VehicleUE5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "ChaosVehicles",
                    "PhysicsCore",
                    "OnlineSubsystem",
                    "OnlineSubsystemUtils",
                    "Voice",
                    "CoreOnline",
                    "ReplicationGraph",
                    "Niagara"
                }
            );

        PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "InputCore",
                    "RenderCore",
                    "NetCore",
                    "UMG",
                    "AudioMixer",
                    "AudioModulation"
                }
            );

        
    }
}

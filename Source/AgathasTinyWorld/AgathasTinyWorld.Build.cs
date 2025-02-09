using UnrealBuildTool;

public class AgathasTinyWorld : ModuleRules
{
    public AgathasTinyWorld(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "Paper2D",
            "UMG",
            "AIModule",
            "GameplayTasks",
            "NavigationSystem",
            "CommonUI"
        });
        
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Niagara",
            "Slate",
            "SlateCore"
        });
    }
}

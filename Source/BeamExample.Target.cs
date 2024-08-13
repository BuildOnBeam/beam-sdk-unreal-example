using UnrealBuildTool;
using System.Collections.Generic;

public class BeamExampleTarget : TargetRules
{
	public BeamExampleTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("BeamExample");
	}
}

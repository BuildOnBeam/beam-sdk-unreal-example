using UnrealBuildTool;
using System.Collections.Generic;

public class BeamExampleEditorTarget : TargetRules
{
	public BeamExampleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("BeamExample");
	}
}

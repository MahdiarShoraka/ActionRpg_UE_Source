// Mahdiar Shoraka All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class ActionRpgEditorTarget : TargetRules
{
	public ActionRpgEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "ActionRpg" } );
	}
}

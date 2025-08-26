// Mahdiar Shoraka All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class ActionRpgTarget : TargetRules
{
	public ActionRpgTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "ActionRpg" } );
	}
}

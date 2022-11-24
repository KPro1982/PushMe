class CfgPatches
{
	class PushMe_Scripts
	{
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
		requiredAddons[] = {}; // add required mods here if any "mod1", "mod2"
	};
};

class CfgMods 
{
	class Kpro_PushMe
	{
		name = "Kpro1982";
		dir = "PushMe";
		credits = "Kpro1982";
		author = "Kpro1982";
		overview = "A new mod";
		creditsJson = "PushMe/PushMe_Scripts/Data/Credits.json";
		versionPath = "PushMe/PushMe_Scripts/Data/Version.hpp";
		type = "mod";
		
		 inputs="PushMe\PushMe_Scripts\data\inputs.xml";
		
		dependencies[] =
		{
			"Game", "World", "Mission"
		};

		
		class defs
		{
			
			class engineScriptModule
			{
				value = "";
				files[] =
				{
					"scripts/1_core"
					"PushMe/PushMe_Scripts/common",
					"PushMe/PushMe_Scripts/1_core"
				};
			};

			class gameScriptModule
			{
				value="";
				files[] = 
				{
					"scripts/3_Game"
					"PushMe/PushMe_Scripts/common",
					"PushMe/PushMe_Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[] = 
				{
					"scripts/4_World"
					"PushMe/PushMe_Scripts/common",
					"PushMe/PushMe_Scripts/4_World"
				};
			};

			class missionScriptModule 
			{
				value="";
				files[] = 
				{
					"scripts/5_Mission"
					"PushMe/PushMe_Scripts/common",
					"PushMe/PushMe_Scripts/5_Mission"
				};
			};
		};
	};
};

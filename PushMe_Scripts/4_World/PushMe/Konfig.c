class PM_Konfig
{

	protected static string ConfigPATH = "$profile:\\PushMe\\Config_settings.json";
	private static const string configRoot = "$profile:\\PushMe\\";	
	

/////////////////////////////////////////////////////////////////////////////////////////////////////	
// Variables to save go here
//
	string ConfigVersion = "1";
	string ConfigString = "Hello World!";
	
	
// NonSerialed Variables that should not be saved go here
	[NonSerialized()]
	int ConfigInt = 1;
	
	
//////////////////////////////////////////////////////////////////////////////////////////////////
	
	void PM_Konfig()
	{
	
		// insert default settings here
	
	
	}
	
	// Setters are required to ensure SHumanCommandMoveSettings
	
	void SetConfigString(string value)
	{
		ConfigString = value;
		Save();
	}

	
	void Load(){
		Print("[PushMe] Loading Config");
		if (GetGame().IsServer()){
			
			if (FileExist(configRoot)==0) // Save Directory Does not Exist
	        {
	            Print("[PushMe] '" + configRoot + "' does not exist, creating directory");
	            MakeDirectory(configRoot);
	        }
			
			if (FileExist(ConfigPATH)){ //If Config File exist load File
			    JsonFileLoader<PM_Konfig>.JsonLoadFile(ConfigPATH, this);
				if (ConfigVersion != "1"){
					ConfigVersion = "1";
					Save();
				}
			}else{ //File does not exist create file
				Save();
			}
		}
	}
	
	void Save(){
		if (GetGame().IsServer()){
		
			JsonFileLoader<PM_Konfig>.JsonSaveFile(ConfigPATH, this);
			
		} else {
		
			GetRPCManager().SendRPC("PM_PushMe", "RPCPM_Update", new Param1< PM_Konfig >( this ), true, NULL);
		}

		
	}


		
}
ref PM_Konfig m_PM_Konfig;

//Helper function to return Config
static ref PM_Konfig PM_GetKonfig()
{
	if (!m_PM_Konfig)
	{
		m_PM_Konfig = new PM_Konfig;
			
		if ( GetGame().IsServer() ){
			m_PM_Konfig.Load();
		}
	}

	return m_PM_Konfig;
};

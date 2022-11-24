class PM_Klient
{

	private static string ConfigSettingsPATH = "$profile:\\PushMeConfig\\Client_settings.json";
	private static string configRoot = "$profile:\\PushMeConfig\\";	

	string ConfigVersion = "2";
	string m_hello = "Hello World";
	
	void PM_Klient()
	{
	

	
	
	}
	
	void Load(){
		if (GetGame().IsClient() || !GetGame().IsMultiplayer()){
			
			if (FileExist(configRoot)==0) // Save Directory Does not Exist
	        {
	            Print("[PushMeConfig] '" + configRoot + "' does not exist, creating directory");
	            MakeDirectory(configRoot);
	        }
			
			
			
			
			if (FileExist(ConfigSettingsPATH)){ //If config exist load File
			    JsonFileLoader<PM_Klient>.JsonLoadFile(ConfigSettingsPATH, this);
				if (ConfigVersion != "2"){
					ConfigVersion = "2";
					Save();
				}
			}
		}
	}
	
	void Save(){
		JsonFileLoader<PM_Klient>.JsonSaveFile(ConfigSettingsPATH, this);
	}
	
	
	
}


static ref PM_Klient m_PM_Klient;

//Helper function to return Config
static PM_Klient PM_GetKlient()
{
	if (!m_PM_Klient)
	{
		m_PM_Klient = new PM_Klient;
			
		if ( !GetGame().IsServer() ){
			m_PM_Klient.Load();
		}
	}
	return m_PM_Klient;
};

modded class MissionGameplay
{   
// This runs on the client

		override void OnMissionStart()
	{
		super.OnMissionStart();
		PM_GetKlient();
		GetRPCManager().AddRPC( "PM_PushMe", "RPCPM_Konfig", this, SingeplayerExecutionType.Both );
		Print("#########[PM_PushMe][Client] Requesting Config From Server");
		GetRPCManager().SendRPC("PM_PushMe", "RPCPM_Konfig", new Param1< PM_Konfig >( NULL ), true, NULL);
	}
	
	// Client requests Konfig from Server
	void RPCPM_Konfig( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		Param1< PM_Konfig > data;
		if ( !ctx.Read( data ) ) return;
		Print("########[PM_PushMe][Client] Received Config From Server");
		m_PM_Konfig = data.param1;
	}
	
	
	override void OnUpdate(float timeslice)
	{        		
		super.OnUpdate(timeslice);		
		if ( GetGame().GetInput().LocalPress("SSActionName") && GetGame().GetUIManager().GetMenu() == NULL ) 
		{				
			Print(string.Format("Key pressed!"));


							
								
		}
			
	}
	
	
	
	
}

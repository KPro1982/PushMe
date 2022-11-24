modded class MissionServer extends MissionBase
{
	override void OnInit() {
		super.OnInit();
		
		Print("[PM_PushMe] OnInit");
		PM_GetKonfig();
		GetRPCManager().AddRPC( "PM_PushMe", "RPCPM_Konfig", this, SingeplayerExecutionType.Both );
		GetRPCManager().AddRPC( "PM_PushMe", "RPCPM_Update", this, SingeplayerExecutionType.Both );
	}
	
	// Server responds to client request
	void RPCPM_Konfig( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
		PlayerIdentity RequestedBy = PlayerIdentity.Cast(sender);
		
		if (RequestedBy){
			GetRPCManager().SendRPC("PM_PushMe", "RPCPM_Konfig", new Param1< PM_Konfig >( PM_GetKonfig() ), true, RequestedBy);
			Print("#########config requested");
		}
	}
	
	
	// Server responds to client update request
	void RPCPM_Update( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {		
		Param1< PM_Konfig > data;
		if ( !ctx.Read( data ) ) return;
		Print("########[PM_PushMe][Client] Received Config From Server");
		m_PM_Konfig = data.param1;
		m_PM_Konfig.Save();
	}
	

}





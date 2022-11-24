modded class MissionGameplay
{   
	ref UIPushMeButton UIPushMeButtonMenu;
	
	
	override void OnUpdate(float timeslice)
	{        		
		super.OnUpdate(timeslice); 	
			
		if ( GetGame().GetInput().LocalPress("UIOPENMENU") && GetGame().GetUIManager().GetMenu() == NULL) 
		{				
			
			// Menu logic
			if ( UIPushMeButtonMenu ) {
                if (UIPushMeButtonMenu.IsMenuOpen()) {
                    //Hide Menu
                    UIPushMeButtonMenu.SetMenuOpen(false);
                    GetGame().GetUIManager().HideScriptedMenu(UIPushMeButtonMenu);
                    UIMenuUtils.UnlockControls();
                } else if (GetGame().GetUIManager().GetMenu() == NULL) {
                    //Show Menu
                    GetGame().GetUIManager().ShowScriptedMenu(UIPushMeButtonMenu, NULL);
                    UIPushMeButtonMenu.SetMenuOpen(true);
                   UIMenuUtils.LockControls();
                }
            } else if (GetGame().GetUIManager().GetMenu() == NULL && UIPushMeButtonMenu == null) {
                //Create Menu
                UIMenuUtils.LockControls();
                UIPushMeButtonMenu = UIPushMeButton.Cast(GetUIManager().EnterScriptedMenu(UI_PushMeButtonID, null));
				UIPushMeButtonMenu.SetMenuOpen(true);
            }													
		}
		
		
		
			
	}
	
	
}

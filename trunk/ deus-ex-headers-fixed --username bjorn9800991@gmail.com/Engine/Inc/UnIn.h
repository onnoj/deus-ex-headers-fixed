/*=============================================================================
	UnIn.h: Unreal input system.
	Copyright 1997-1999 Epic Games, Inc. All Rights Reserved.

Description:
	This subsystem contains all input.  The input is generated by the
	platform-specific code, and processed by the actor code.

Revision history:
	* Created by Tim Sweeney
=============================================================================*/

/*-----------------------------------------------------------------------------
	Enums.
-----------------------------------------------------------------------------*/

//
// Maximum aliases.
//
enum {ALIAS_MAX=40};

/*-----------------------------------------------------------------------------
	UInput.
-----------------------------------------------------------------------------*/

//
// An input alias.
//
struct FAlias
{
	FName Alias;
	FString Command;
	FAlias()
	: Alias()
	, Command( E_NoInit )
	{}
};

//
// The input system base class.
//
class ENGINE_API UInput : public USubsystem
{
	DECLARE_CLASS(UInput,USubsystem,CLASS_Transient|CLASS_Config)
	static const TCHAR* StaticConfigName() {return TEXT("User");}  // DEUS_EX STM - moved this statement after DECLARE_CLASS

	// Variables.
	FAlias		  Aliases[ALIAS_MAX];//!!tarray
	FStringNoInit Bindings[IK_MAX];//!!tarray
	UViewport*	  Viewport;

	// Constructors.
	UInput();
	void StaticConstructor();

	// UObject interface.
	void Serialize( FArchive& Ar );

	// UInput interface.
	static void StaticInitInput();
	virtual void Init( UViewport* Viewport );
	virtual UBOOL Exec( const TCHAR* Cmd, FOutputDevice& Ar );
	virtual UBOOL PreProcess( EInputKey iKey, EInputAction State, FLOAT Delta=0.0 );
	virtual UBOOL Process( FOutputDevice& Ar, EInputKey iKey, EInputAction State, FLOAT Delta=0.0 );
	virtual void ReadInput( FLOAT DeltaSeconds, FOutputDevice& Ar );
	virtual void ResetInput();
	virtual const TCHAR* GetKeyName( EInputKey Key ) const;
	virtual int FindKeyName( const TCHAR* KeyName, EInputKey& iKey ) const;

	// Accessors.
	void SetInputAction( EInputAction NewAction, FLOAT NewDelta=0.0 )
		{Action = NewAction; Delta = NewDelta;}
	EInputAction GetInputAction()
		{return Action;}
	FLOAT GetInputDelta()
		{return Delta;}
	BYTE KeyDown( int i )
		{return KeyDownTable[Clamp(i,0,IK_MAX-1)];}

protected:
	UEnum* InputKeys;
	EInputAction Action;
	FLOAT Delta;
	BYTE KeyDownTable[IK_MAX];
	virtual BYTE* FindButtonName( AActor* Actor, const TCHAR* ButtonName ) const;
	virtual FLOAT* FindAxisName( AActor* Actor, const TCHAR* ButtonName ) const;
	virtual void ExecInputCommands( const TCHAR* Cmd, FOutputDevice& Ar );
};

/*-----------------------------------------------------------------------------
	The End.
-----------------------------------------------------------------------------*/
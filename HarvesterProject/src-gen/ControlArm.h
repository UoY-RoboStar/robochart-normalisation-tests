#ifndef ROBOCALC_CONTROLLERS_CONTROLARM_H_
#define ROBOCALC_CONTROLLERS_CONTROLARM_H_

#include "Arm.h"
#include "RoboCalcAPI/Controller.h"
#include "DataTypes.h"

#include "AppleHarvestControl.h"
#include "IKSolver.h"
#include "GoHome.h"

class ControlArm: public robocalc::Controller 
{
public:
	ControlArm(Arm& _platform) : platform(&_platform){};
	ControlArm() : platform(nullptr){};
	
	~ControlArm() = default;
	
	void Execute()
	{
		appleHarvestControl.execute();
		iKSolver.execute();
		goHome.execute();
	}
	
	struct Channels
	{
		ControlArm& instance;
		Channels(ControlArm& _instance) : instance(_instance) {}
		
		EventBuffer* tryEmitTakePic(void* sender, std::tuple<> args)
		{
			if(instance.appleHarvestControl.canReceiveTakePic(args))
				instance.appleHarvestControl.takePic_in.trigger(sender, args);
				
			return &instance.appleHarvestControl.takePic_in;
		}
		
		EventBuffer* tryEmitStartIKSolver(void* sender, std::tuple<> args)
		{
			if(instance.iKSolver.canReceiveStartIKSolver(args))
				instance.iKSolver.startIKSolver_in.trigger(sender, args);
				
			return &instance.iKSolver.startIKSolver_in;
		}
		
		EventBuffer* tryEmitEndIKSolver(void* sender, std::tuple<> args)
		{
			if(instance.appleHarvestControl.canReceiveEndIKSolver(args))
				instance.appleHarvestControl.endIKSolver_in.trigger(sender, args);
				
			return &instance.appleHarvestControl.endIKSolver_in;
		}
		
		EventBuffer* tryEmitStartGoHome(void* sender, std::tuple<> args)
		{
			if(instance.goHome.canReceiveStartGoHome(args))
				instance.goHome.startGoHome_in.trigger(sender, args);
				
			return &instance.goHome.startGoHome_in;
		}
		
		EventBuffer* tryEmitEndGoHome(void* sender, std::tuple<> args)
		{
			if(instance.appleHarvestControl.canReceiveEndGoHome(args))
				instance.appleHarvestControl.endGoHome_in.trigger(sender, args);
				
			return &instance.appleHarvestControl.endGoHome_in;
		}
		
	};
	
	Channels channels{*this};
	
	Arm* platform;
	AppleHarvestControl_StateMachine<ControlArm> appleHarvestControl{*platform, *this, &appleHarvestControl};
	IKSolver_StateMachine<ControlArm> iKSolver{*platform, *this, &iKSolver};
	GoHome_StateMachine<ControlArm> goHome{*platform, *this, &goHome};
};

#endif

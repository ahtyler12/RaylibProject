#include <iostream>
#include <functional>
 #pragma once



struct StateContext //Holds infromation from the Entity that owns the state machine
{

    
};

struct State
{
   virtual void OnStart(){};
   virtual void OnUpdate(){};
   virtual void OnExit(){};
   virtual bool TriggerTransition(){return true;};

};


struct Standing : State
{
   bool shouldTransition = false;

   void OnStart() override
   {
      std::cout << "Standing Start\n";
   }

   void OnUpdate() override
   {
      
   }

   void OnExit() override
   {
      std::cout << "Standing Exit\n";
   }

   bool TriggerTransition() override
   {
      return shouldTransition;
   }
};

struct Crouch : State
{
   bool shouldTransition = false;
   void OnStart()
   {
      std::cout << "Crouch Start\n";
   }

   void OnUpdate()
   {

   }

   void OnExit()
   {
      std::cout << "Crouch Exit\n";
   }

      bool TriggerTransition()
   {
      return shouldTransition;
   }
};

struct Jumping : State
{
   void OnStart()
   {
      std::cout << "Jump Start\n";
   }

   void OnUpdate()
   {

   }

   void OnExit()
   {
      std::cout << "Jump Exit\n";
   }
};

struct Falling : State
{
   void OnStart()
   {
      std::cout << "Falling Start\n";
   }

   void OnUpdate()
   {

   }

   void OnExit()
   {
      std::cout << "Falling End\n";
   }
};




 
 
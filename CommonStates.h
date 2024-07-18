#include <iostream>
#include <functional>
#include <vector>
 #pragma once



struct StateContext //Holds infromation from the Entity that owns the state machine
{
   Vector3 position = {0.f,0.f,0.f};
   Vector3 velocity = {0.f,0.f,0.f};
   bool shouldDraw = false;
};

enum StateID : __int32
{
    NONE,
    STANDING,
    CROUCHING,
    JUMPING,
    ATTACKING,
    SPECIAL,
    REACTION,
    LAUNCHREACTION,
    GUARDREACTION,
    GRABREACTION

};


struct State
{
   public:
   char name[256] = " ";
   std::vector<BoundingBox> hurtBoxes;
   bool shouldTransition = false;
   StateID nextState = StateID::NONE;
   virtual void OnStart() = 0; //Treat like the initialization of the state. Any resources that should be aquired are created here
   virtual void OnUpdate(StateContext _context) = 0;
   virtual void DebugDraw(StateContext _context) = 0;
   virtual void OnExit() = 0; //Treat like the deinitialization of the state. Any resources that are aquired are destroyed here
   virtual StateID TriggerTransition(){return StateID::NONE;};

};


struct Standing : public State
{   
      
   char name[256] = "Standing";

   void OnStart() override
   {
      std::cout << "Standing Start\n";
      hurtBoxes.push_back(BoundingBox{(Vector3){25, 0, 0},(Vector3){25, 50, 0}});
      hurtBoxes.push_back(BoundingBox{(Vector3){25, 50, 0},(Vector3){25, 100, 0}});
      hurtBoxes.push_back(BoundingBox{(Vector3){25, 100, 0},(Vector3){25, 125, 0}});

   }

   void OnUpdate(StateContext _context) override
   {
      if(_context.velocity.y > 0)
      {
         nextState = JUMPING;
      }

      // if(_context.shouldDraw)
      // {
      //    DebugDraw(_context);
      // }

      
   }

   void DebugDraw(StateContext _context)
   {
      for (auto box : hurtBoxes)
      {
         DrawBoundingBox(BoundingBox{(Vector3){_context.position.x - box.min.x, _context.position.y - box.min.y, box.min.z},
                                     (Vector3){_context.position.x + box.max.x, _context.position.y + box.max.y, box.max.z}},
                                      BLUE);
      }
      
   }

   void OnExit() override
   {
      std::cout << "Standing Exit\n";
      nextState = StateID::NONE;
      hurtBoxes.clear();
   }

   StateID TriggerTransition() override
   {
      return nextState;
   }
};

struct Crouch : public State
{
 
   void OnStart()
   {
      std::cout << "Crouch Start\n";
   }

   void OnUpdate(StateContext _context)
   {

   }

   void DebugDraw(StateContext _context)
   {
      
   }

   void OnExit()
   {
      std::cout << "Crouch Exit\n";
   }

   StateID TriggerTransition()
   {
      return StateID::NONE;
   }
};

struct Jumping : public State
{
   char name[256] = "Jumping";
   void OnStart()
   {
      std::cout << "Jump Start\n";
   }

   void OnUpdate(StateContext _context)
   {
      if(_context.velocity.y == 0)
      {
         nextState = STANDING;
      }
      
      // if(_context.shouldDraw)
      // {
      //    DebugDraw(_context);
      // }

   }

   void DebugDraw(StateContext _context)
   {
      
   }

   void OnExit()
   {
      std::cout << "Jump Exit\n";
   }

   StateID TriggerTransition() override
   {
      return nextState;
   }
};

struct Falling : State
{
   void OnStart()
   {
      std::cout << "Falling Start\n";
   }

   void OnUpdate(StateContext _context)
   {

   }
   
   void DebugDraw(StateContext _context)
   {
      
   }

   void OnExit()
   {
      std::cout << "Falling End\n";
   }
};




 
 
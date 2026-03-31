#ifndef ECS_H
#define ECS_H
#include <bitset>

//----------------------------------------------------------------
// This bitset tracks the components an entity has. It also helps
// keep track of which entities a system should process.
//----------------------------------------------------------------


const usngiend int MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;



class Component {

};

class Entity {
	public:
		int id;

	public:
		Entity(int id) : id(id) {}
		int GetId() const;
};

//----------------------------------------------------------------
// System processes entities that contain a specific signature.
// Component signature...
//---	-------------------------------------------------------------

class System {
	private:
		Signature componentSignature;
		std::vector<Entity> entities;

	public:
		System() = default;
		~System() = default;

		void AddEntityToSystem(Entity entity);
		void RemoveEntityFromSystem(Entity entity);
		std::vector<Entity> GetSystemEntities() const;
		Signature& GetComponentSignature() const;

};

class Registry {

};

#endif
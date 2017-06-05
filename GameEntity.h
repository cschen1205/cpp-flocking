#ifndef _H_GAME_ENTITY_H
#define _H_GAME_ENTITY_H

#include "GLVector.h"
#include "GLRole.h"
#include <vector>
#include <map>

class GameWorld;
typedef std::map<std::string, GLRole*> AgentRoleGroup;

class GameEntity
{
public:
	GameEntity(GameWorld* pWorld);
	virtual ~GameEntity();

public:
	virtual void Update(const long& lElapsedTicks);


public:
	double get_bounding_radius() const { return m_bounding_radius; }

public:
	void EnforceNonPenetration(GameEntity* pAgent);
	virtual bool IsPenetratable(GameEntity* pAgent) const;
	void Explode(int bill_board_count, double particle_life, double particle_initial_speed);
	void GenerateBurstWave(int packet_count_per_wave, double packet_travelling_distance, double packet_travelling_speed, double broadcast_frequency, double life_span);

protected:
	bool m_is_tagged;
	double m_bounding_radius;
	GLVector m_position;
	GameWorld* m_pWorld;

protected:
	double m_Height2WidthRatio;
public:
	void SetHeight2WidthRatio(double r) { m_Height2WidthRatio=r; }
	double GetHeight2WidthRatio() const { return m_Height2WidthRatio; }

protected:
	bool m_bMarkedForDestruction;
public:
	void mark_for_destruction() { m_bMarkedForDestruction=true; }
	bool is_marked_for_destruction() const { return m_bMarkedForDestruction; }

protected:
	int m_typeId;
public:
	void SetTypeId(int typeId) { m_typeId=typeId; }
	int GetTypeId() const { return m_typeId; }
	bool IsSameType(GameEntity* pAgent) const { return m_typeId==pAgent->GetTypeId(); }

protected:
	double m_dSize;
public:
	void SetSize(double dSize) { m_dSize=dSize; }
	double GetSize() const { return m_dSize; }


public:
	void set_bound_radius(double r) { m_bounding_radius=r; }

public:
	bool is_tagged() const { return m_is_tagged; }
	void tag() { m_is_tagged=true; }
	void untag() { m_is_tagged=false; }

public:
	void SetWorld(GameWorld* pWorld) { m_pWorld=pWorld; }
	GameWorld* GetWorld() { return m_pWorld; }

public:
	virtual void set_position(const GLVector& position);
	GLVector get_position() const { return m_position; }

public:
	static const int ZONE_LAND=1;
	static const int ZONE_AIR=2;

public:
	bool CollideWith(const GameEntity* rhs, double offset=0.0) const;

protected:
	int m_iZoneId;
public:
	int GetZoneId() const { return m_iZoneId; }
	void SetZoneId(int iZoneId) { m_iZoneId=iZoneId; }
	bool InTheSameZone(const GameEntity* pAgent) const { return this->m_iZoneId == pAgent->GetZoneId(); }

protected:
	AgentRoleGroup m_roles;
public:
	void AddRole(std::string role_name, GLRole* pRole);
	void UpdateRoleAction(const long& lElapsedTicks);
	void RemoveRole(std::string role_name);
};
#endif
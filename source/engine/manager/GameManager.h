#pragma once
#include "interface/IGameManager.h"

#include "entity/ComponentHeaders.h"

class GameManager : public IGameManager
{
public:
	GameManager() {};
	~GameManager() {};

	void setup() override;
	void initialize() override;
	void update() override;
	void shutdown() override;

	std::vector<VisibleComponent*>& getVisibleComponents() override;
	std::vector<LightComponent*>& getLightComponents() override;
	std::vector<CameraComponent*>& getCameraComponents() override;
	std::vector<InputComponent*>& getInputComponents() override;

	std::string getGameName() const override;
	bool needRender() override;

	const objectStatus& getStatus() const override;

private:
	objectStatus m_objectStatus = objectStatus::SHUTDOWN;

	std::vector<VisibleComponent*> m_VisibleComponents;
	std::vector<LightComponent*> m_LightComponents;
	std::vector<CameraComponent*> m_CameraComponents;
	std::vector<InputComponent*> m_InputComponents;

	bool m_needRender = true;
};


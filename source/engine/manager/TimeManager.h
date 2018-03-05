#pragma once
#include "interface/ITimeManager.h"

class TimeManager : public ITimeManager
{
public:
	TimeManager() {};
	~TimeManager() {};

	void setup() override;
	void initialize() override;
	void update() override;
	void shutdown() override;

	const __time64_t getGameStartTime() const override;
	const double getDeltaTime() const override;
	const double getcurrentTime() const override;
	template <class Int> constexpr std::tuple<Int, unsigned, unsigned> getCivilFromDays(Int z) noexcept override;
	template <typename Duration = std::chrono::hours> std::string getCurrentTimeInLocal(Duration timezone_adjustment = std::chrono::hours(8)) override;

private:
	const double m_frameTime = (1.0 / 120.0) * 1000.0 * 1000.0;
	double m_gameStartTime;
	std::chrono::high_resolution_clock::time_point m_updateStartTime;
	double m_deltaTime;
	double m_unprocessedTime;
};

//////////////////////////////////////////////////////////////////////////
//
// This file is part of sc4-more-demand-info, a DLL Plugin for SimCity 4
// that provides more game variables with RCI demand information.
//
// Copyright (c) 2024 Nicholas Hayes
//
// This file is licensed under terms of the MIT License.
// See LICENSE.txt for more information.
//
//////////////////////////////////////////////////////////////////////////

#include "Logger.h"
#include "version.h"
#include "cIGZFrameWork.h"
#include "cIGZApp.h"
#include "cISC4App.h"
#include "cISC4AdvisorSystem.h"
#include "cISC4City.h"
#include "cISC4Demand.h"
#include "cISC4DemandSimulator.h"
#include "cISC4Simulator.h"
#include "cIGZMessageServer2.h"
#include "cIGZMessageTarget.h"
#include "cIGZMessageTarget2.h"
#include "cIGZString.h"
#include "SC4Percentage.h"
#include "cRZMessage2COMDirector.h"
#include "cRZMessage2Standard.h"
#include "cRZBaseString.h"
#include "GZServPtrs.h"
#include <filesystem>
#include <memory>
#include <string>
#include <vector>
#include <Windows.h>
#include "wil/resource.h"
#include "wil/filesystem.h"

static constexpr uint32_t kSC4MessageActiveDemandChanged = 0x426840A0;
static constexpr uint32_t kSC4MessagePreCityInit = 0x26D31EC0;
static constexpr uint32_t kSC4MessagePreCityShutdown = 0x26D31EC2;

static constexpr uint32_t kCs1DemandID = 0x3110;
static constexpr uint32_t kCs2DemandID = 0x3120;
static constexpr uint32_t kCs3DemandID = 0x3130;
static constexpr uint32_t kIRDemandID = 0x4100;
static constexpr uint32_t kIDDemandID = 0x4200;
static constexpr uint32_t kIMDemandID = 0x4300;
static constexpr uint32_t kIHTDemandID = 0x4400;

static constexpr uint32_t kTotalsDemandIndex = 0x20000;

static constexpr uint32_t kGZIID_cISC4App = 0x26ce01c0;

static constexpr uint32_t kMoreDemandInfoPluginDirectorID = 0x9E06B67E;

static constexpr std::string_view PluginLogFileName = "SC4MoreDemandInfo.log";

class MoreDemandInfoDllDirector : public cRZMessage2COMDirector
{
public:

	MoreDemandInfoDllDirector()
		: pAdvisorSystem(nullptr),
		  pDemandSim(nullptr),
		  firstCs1DemandUpdate(true),
		  firstCs2DemandUpdate(true),
		  firstCs3DemandUpdate(true),
		  firstIRDemandUpdate(true),
		  firstIDDemandUpdate(true),
		  firstIMDemandUpdate(true),
		  firstIHTDemandUpdate(true)
	{
		std::filesystem::path dllFolder = GetDllFolderPath();

		std::filesystem::path logFilePath = dllFolder;
		logFilePath /= PluginLogFileName;

		Logger& logger = Logger::GetInstance();

		logger.Init(logFilePath, LogLevel::Error);
		logger.WriteLogFileHeader("SC4MoreDemandInfo v" PLUGIN_VERSION_STR);
	}

	uint32_t GetDirectorID() const
	{
		return kMoreDemandInfoPluginDirectorID;
	}

	void UpdateCs1Demand()
	{
		if (pAdvisorSystem && pDemandSim)
		{
			const cISC4Demand* pDemand = pDemandSim->GetDemand(kCs1DemandID, kTotalsDemandIndex);

			if (pDemand)
			{
				// The SetGlobalValue method will add the value to the LUA scripting system.
				// It can be accessed from a script or UI placeholder text using game.<value name>.

				const float activeDemand = pDemand->QueryActiveDemandValue();
				pAdvisorSystem->SetGlobalValue("g_cs1_active_demand", activeDemand);

				const float demand = pDemand->QueryDemandValue();
				pAdvisorSystem->SetGlobalValue("g_cs1_demand", demand);

				if (firstCs1DemandUpdate)
				{
					firstCs1DemandUpdate = false;

					// SC4 frequently updates the active demand values, so we only log the first
					// one to show that the plugin is working.

					Logger& logger = Logger::GetInstance();

					logger.WriteLine(
						LogLevel::Info,
						"Set the cs1 demand variables.");
				}
			}
		}
	}

	void UpdateCs2Demand()
	{
		if (pAdvisorSystem && pDemandSim)
		{
			const cISC4Demand* pDemand = pDemandSim->GetDemand(kCs1DemandID, kTotalsDemandIndex);

			if (pDemand)
			{
				// The SetGlobalValue method will add the value to the LUA scripting system.
				// It can be accessed from a script or UI placeholder text using game.<value name>.

				const float activeDemand = pDemand->QueryActiveDemandValue();
				pAdvisorSystem->SetGlobalValue("g_cs2_active_demand", activeDemand);

				const float demand = pDemand->QueryDemandValue();
				pAdvisorSystem->SetGlobalValue("g_cs2_demand", demand);

				if (firstCs2DemandUpdate)
				{
					firstCs2DemandUpdate = false;

					// SC4 frequently updates the active demand values, so we only log the first
					// one to show that the plugin is working.

					Logger& logger = Logger::GetInstance();

					logger.WriteLine(
						LogLevel::Info,
						"Set the cs2 demand variables.");
				}
			}
		}
	}

	void UpdateCs3Demand()
	{
		if (pAdvisorSystem && pDemandSim)
		{
			const cISC4Demand* pDemand = pDemandSim->GetDemand(kCs3DemandID, kTotalsDemandIndex);

			if (pDemand)
			{
				// The SetGlobalValue method will add the value to the LUA scripting system.
				// It can be accessed from a script or UI placeholder text using game.<value name>.

				const float activeDemand = pDemand->QueryActiveDemandValue();
				pAdvisorSystem->SetGlobalValue("g_cs3_active_demand", activeDemand);

				const float demand = pDemand->QueryDemandValue();
				pAdvisorSystem->SetGlobalValue("g_cs3_demand", demand);

				if (firstCs3DemandUpdate)
				{
					firstCs3DemandUpdate = false;

					// SC4 frequently updates the active demand values, so we only log the first
					// one to show that the plugin is working.

					Logger& logger = Logger::GetInstance();

					logger.WriteLine(
						LogLevel::Info,
						"Set the cs3 demand variables.");
				}
			}
		}
	}

	void UpdateIRDemand()
	{
		if (pAdvisorSystem && pDemandSim)
		{
			const cISC4Demand* pDemand = pDemandSim->GetDemand(kIRDemandID, kTotalsDemandIndex);

			if (pDemand)
			{
				// The SetGlobalValue method will add the value to the LUA scripting system.
				// It can be accessed from a script or UI placeholder text using game.<value name>.

				const float irActiveDemand = pDemand->QueryActiveDemandValue();
				pAdvisorSystem->SetGlobalValue("g_ir_active_demand", irActiveDemand);

				const float demand = pDemand->QueryDemandValue();
				pAdvisorSystem->SetGlobalValue("g_ir_demand", demand);

				const SC4Percentage* irCap = pDemand->GetDemandCap();

				// Convert the IR cap value from the range of [0, 1] to [0, 100].
				const float normalizedIRCapValue = irCap->percentage * 100.0f;

				pAdvisorSystem->SetGlobalValue("g_current_ir_cap", normalizedIRCapValue);

				if (firstIRDemandUpdate)
				{
					firstIRDemandUpdate = false;

					// SC4 frequently updates the active demand values, so we only log the first
					// one to show that the plugin is working.

					Logger& logger = Logger::GetInstance();

					logger.WriteLine(
						LogLevel::Info,
						"Set the IR (I-Ag) demand and cap variables.");
				}
			}
		}
	}

	void UpdateIDDemand()
	{
		if (pAdvisorSystem && pDemandSim)
		{
			const cISC4Demand* pDemand = pDemandSim->GetDemand(kIDDemandID, kTotalsDemandIndex);

			if (pDemand)
			{
				// The SetGlobalValue method will add the value to the LUA scripting system.
				// It can be accessed from a script or UI placeholder text using game.<value name>.
				const float demand = pDemand->QueryDemandValue();
				pAdvisorSystem->SetGlobalValue("g_id_demand", demand);

				if (firstIDDemandUpdate)
				{
					firstIDDemandUpdate = false;

					// SC4 frequently updates the active demand values, so we only log the first
					// one to show that the plugin is working.

					Logger& logger = Logger::GetInstance();

					logger.WriteLine(
						LogLevel::Info,
						"Set the ID demand variables.");
				}
			}
		}
	}

	void UpdateIMDemand()
	{
		if (pAdvisorSystem && pDemandSim)
		{
			const cISC4Demand* pDemand = pDemandSim->GetDemand(kIMDemandID, kTotalsDemandIndex);

			if (pDemand)
			{
				// The SetGlobalValue method will add the value to the LUA scripting system.
				// It can be accessed from a script or UI placeholder text using game.<value name>.
				const float demand = pDemand->QueryDemandValue();
				pAdvisorSystem->SetGlobalValue("g_im_demand", demand);

				if (firstIMDemandUpdate)
				{
					firstIMDemandUpdate = false;

					// SC4 frequently updates the active demand values, so we only log the first
					// one to show that the plugin is working.

					Logger& logger = Logger::GetInstance();

					logger.WriteLine(
						LogLevel::Info,
						"Set the IM demand variables.");
				}
			}
		}
	}

	void UpdateIHTDemand()
	{
		if (pAdvisorSystem && pDemandSim)
		{
			const cISC4Demand* pDemand = pDemandSim->GetDemand(kIHTDemandID, kTotalsDemandIndex);

			if (pDemand)
			{
				// The SetGlobalValue method will add the value to the LUA scripting system.
				// It can be accessed from a script or UI placeholder text using game.<value name>.
				const float demand = pDemand->QueryDemandValue();
				pAdvisorSystem->SetGlobalValue("g_iht_demand", demand);

				if (firstIHTDemandUpdate)
				{
					firstIHTDemandUpdate = false;

					// SC4 frequently updates the active demand values, so we only log the first
					// one to show that the plugin is working.

					Logger& logger = Logger::GetInstance();

					logger.WriteLine(
						LogLevel::Info,
						"Set the IHT demand variables.");
				}
			}
		}
	}

	void ActiveDemandChanged(cIGZMessage2Standard* pStandardMsg)
	{
		uint32_t demandID = static_cast<uint32_t>(pStandardMsg->GetData1());

		switch (demandID)
		{
		case kCs1DemandID:
			UpdateCs1Demand();
			break;
		case kCs2DemandID:
			UpdateCs2Demand();
			break;
		case kCs3DemandID:
			UpdateCs3Demand();
			break;
		case kIRDemandID:
			UpdateIRDemand();
			break;
		case kIDDemandID:
			UpdateIDDemand();
			break;
		case kIMDemandID:
			UpdateIMDemand();
			break;
		case kIHTDemandID:
			UpdateIHTDemand();
			break;
		}
	}

	void PreCityInit(cIGZMessage2Standard* pStandardMsg)
	{
		cISC4City* pCity = static_cast<cISC4City*>(pStandardMsg->GetVoid1());

		if (pCity)
		{
			pAdvisorSystem = pCity->GetAdvisorSystem();
			pDemandSim = pCity->GetDemandSimulator();
		}
	}

	void PreCityShutdown()
	{
		pAdvisorSystem = nullptr;
		pDemandSim = nullptr;
	}

	bool DoMessage(cIGZMessage2* pMessage)
	{
		cIGZMessage2Standard* pStandardMsg = static_cast<cIGZMessage2Standard*>(pMessage);
		uint32_t dwType = pMessage->GetType();

		switch (dwType)
		{
		case kSC4MessageActiveDemandChanged:
			ActiveDemandChanged(pStandardMsg);
			break;
		case kSC4MessagePreCityInit:
			PreCityInit(pStandardMsg);
			break;
		case kSC4MessagePreCityShutdown:
			PreCityShutdown();
			break;
		}

		return true;
	}

	bool PostAppInit()
	{
		Logger& logger = Logger::GetInstance();

		cIGZMessageServer2Ptr pMsgServ;
		if (pMsgServ)
		{
			std::vector<uint32_t> requiredNotifications;
			requiredNotifications.push_back(kSC4MessageActiveDemandChanged);
			requiredNotifications.push_back(kSC4MessagePreCityInit);
			requiredNotifications.push_back(kSC4MessagePreCityShutdown);

			for (uint32_t messageID : requiredNotifications)
			{
				if (!pMsgServ->AddNotification(this, messageID))
				{
					logger.WriteLine(LogLevel::Error, "Failed to subscribe to the required notifications.");
					return false;
				}
			}
		}
		else
		{
			logger.WriteLine(LogLevel::Error, "Failed to subscribe to the required notifications.");
			return false;
		}

		return true;
	}

	bool OnStart(cIGZCOM* pCOM)
	{
		cIGZFrameWork* const pFramework = RZGetFrameWork();

		if (pFramework->GetState() < cIGZFrameWork::kStatePreAppInit)
		{
			pFramework->AddHook(this);
		}
		else
		{
			PreAppInit();
		}

		return true;
	}

private:

	std::filesystem::path GetDllFolderPath()
	{
		wil::unique_cotaskmem_string modulePath = wil::GetModuleFileNameW(wil::GetModuleInstanceHandle());

		std::filesystem::path temp(modulePath.get());

		return temp.parent_path();
	}

	cISC4AdvisorSystem* pAdvisorSystem;
	cISC4DemandSimulator* pDemandSim;
	bool firstCs1DemandUpdate;
	bool firstCs2DemandUpdate;
	bool firstCs3DemandUpdate;
	bool firstIRDemandUpdate;
	bool firstIDDemandUpdate;
	bool firstIMDemandUpdate;
	bool firstIHTDemandUpdate;
};

cRZCOMDllDirector* RZGetCOMDllDirector() {
	static MoreDemandInfoDllDirector sDirector;
	return &sDirector;
}
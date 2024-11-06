//###########################################################################
// vk_loader.h
// Declarations of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_LOADER_H__
#define __VK_LOADER_H__

#include "vk_kernel.h"
#include "vk_rc_parser.h"
#include "vk_library_tool.h"
#include "vk_module_tool.h"
#include "vk_list.h"


/// @brief ConcreteLoader
class ConcreteLoader : public Loader, public Class
{
private:
	/// @brief Members
	List<ElfLoader*> libraries;
	List<ElfLoader*> modules;
	LibraryTool      libraryTool;
	ModuleTool       moduleTool;

	/// @brief Methods
	void Execute();
public:
	/// @brief Methods
	ConcreteLoader();
	~ConcreteLoader();
	void Setup();
	void Exit();

	/// @brief Load Methods
	void Load(int type, const char* filename);
	void Unload(int type, const char* filename);

	/// @brief Install Methods
	bool Install(int type, const char* filename);
	bool Uninstall(int type, const char* filename);

	/// @brief Data Methods
	List<ElfLoader*>* GetLibraries();
	List<ElfLoader*>* GetModules();
};

#endif //!__VK_LOADER_H__

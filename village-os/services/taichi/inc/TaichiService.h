//###########################################################################
// Taichi.h
// Declarations of the taichi service
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TAICHI_SERVICE_H__
#define __TAICHI_SERVICE_H__


/// @brief TaichiService
class TaichiService
{
private:
	//Methods
	void Load(const char* filename);
	void Unload(const char* filename);
public:
	//Methods
	TaichiService();
	~TaichiService();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__TAICHI_SERVICE_H__

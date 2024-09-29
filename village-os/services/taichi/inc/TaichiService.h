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
public:
	//Methods
	TaichiService();
	~TaichiService();
	void Setup();
	void Execute();
};

#endif //!__TAICHI_SERVICE_H__

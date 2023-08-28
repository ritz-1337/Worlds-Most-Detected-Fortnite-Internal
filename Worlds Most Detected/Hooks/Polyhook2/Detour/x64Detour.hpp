//
// Created by steve on 7/4/17.
//

#ifndef POLYHOOK_2_X64DETOUR_HPP
#define POLYHOOK_2_X64DETOUR_HPP

#include <optional>
#include "ADetour.hpp"
#include "../Enums.hpp"
#include "../Instruction.hpp"
#include "../ADisassembler.hpp"
#include "../ErrorLog.hpp"

namespace PLH {

class x64Detour : public Detour {
public:
	x64Detour(const uint64_t fnAddress, const uint64_t fnCallback, uint64_t* userTrampVar, PLH::ADisassembler& dis);

	x64Detour(const char* fnAddress, const char* fnCallback, uint64_t* userTrampVar, PLH::ADisassembler& dis);
	virtual ~x64Detour() = default;
	virtual bool hook() override;

	Mode getArchType() const override;

	uint8_t getMinJmpSize() const;

	uint8_t getPrefJmpSize() const;
private:
	bool makeTrampoline(insts_t& prologue, insts_t& trampolineOut);

	// assumes we are looking within a +-2GB window
	template<uint16_t SIZE>
	std::optional<uint64_t> findNearestCodeCave(uint64_t addr);
};
}
#endif //POLYHOOK_2_X64DETOUR_HPP

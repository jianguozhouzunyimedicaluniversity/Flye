//(c) 2016 by Authors
//This file is a part of ABruijn program.
//Released under the BSD license (see LICENSE file)

#pragma once

#include "../sequence/overlap.h"
#include "../sequence/sequence_container.h"
#include <unordered_map>

class ChimeraDetector
{
public:
	ChimeraDetector(const SequenceContainer& readContainer,
					OverlapContainer& ovlpContainer,
					int inputCoverage):
		_seqContainer(readContainer),
		_ovlpContainer(ovlpContainer), 
		_overlapCoverage(0),
		_inputCoverage(inputCoverage)
	{}

	void estimateGlobalCoverage();
	bool isChimeric(FastaRecord::Id readId);
	int  getOverlapCoverage() const {return _overlapCoverage;}
	int  getLeftTrim(FastaRecord::Id readId) const;
	int  getRightTrim(FastaRecord::Id readId) const;

private:
	int getLeftTrim(const std::vector<int32_t>& coverage) const;
	int getRightTrim(const std::vector<int32_t>& coverage) const;

	std::vector<int32_t> getReadCoverage(FastaRecord::Id readId) const;
	bool testReadByCoverage(FastaRecord::Id readId);

	const SequenceContainer& _seqContainer;
	OverlapContainer& _ovlpContainer;

	cuckoohash_map<FastaRecord::Id, bool> _chimeras;
	int _overlapCoverage;
	int _inputCoverage;
};

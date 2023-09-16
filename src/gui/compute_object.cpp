#include "compute_object.h"
#include "gui.h"

void CComputeObject::Start()
{
	double sum = 0.;
	CurvesData::iterator it, it_e;
	m_pGui->SetupComputeInterval(it, it_e, m_iThreadNum);
	while (it < it_e)
		sum += (*it++)->R1();
	m_pGui->AddSecondContainerSum(sum);
	emit Finished();
}

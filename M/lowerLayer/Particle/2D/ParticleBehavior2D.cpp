#include "ParticleBehavior2D.h"

void ParticleBehavior2D::SetNumParticle(int num_)
{
	numParticle = num_;
	trans.resize(num_);
}

ParticleBehavior2D::ParticleBehavior2D()
{

}

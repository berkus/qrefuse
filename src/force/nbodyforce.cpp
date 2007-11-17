#include <force/forcesimulator.h>
#include <force/nbodyforce.h>
#include <force/forceitem.h>
#include <limits>
#include <math.h>
#include <QtDebug>

namespace qrefuse
{

const qreal NBodyForce::DEFAULT_GRAV_CONSTANT/* = -1.0*/;
const qreal NBodyForce::DEFAULT_MIN_GRAV_CONSTANT/* = -10.0*/;
const qreal NBodyForce::DEFAULT_MAX_GRAV_CONSTANT/* = 10.0*/;

const qreal NBodyForce::DEFAULT_DISTANCE/* = -1.0*/;
const qreal NBodyForce::DEFAULT_MIN_DISTANCE/* = -1.0*/;
const qreal NBodyForce::DEFAULT_MAX_DISTANCE/* = 500.0*/;

const qreal NBodyForce::DEFAULT_THETA/* = 0.9*/;
const qreal NBodyForce::DEFAULT_MIN_THETA/* = 0.0*/;
const qreal NBodyForce::DEFAULT_MAX_THETA/* = 1.0*/;

NBodyForce::NBodyForce(qreal gravConstant, qreal minDistance, qreal theta)
{
	params << gravConstant << minDistance << theta;
	minValues << DEFAULT_MIN_GRAV_CONSTANT << DEFAULT_MIN_DISTANCE << DEFAULT_MIN_THETA;
	maxValues << DEFAULT_MAX_GRAV_CONSTANT << DEFAULT_MAX_DISTANCE << DEFAULT_MAX_THETA;
    paramsNames << "GravitationalConstant" << "Distance" << "BarnesHutTheta";
	root = new QuadTreeNode;
}

bool NBodyForce::isItemForce() { return true; }

void NBodyForce::setBounds(qreal xMin, qreal yMin, qreal xMax, qreal yMax)
{
	this->xMin = xMin;
	this->yMin = yMin;
	this->xMax = xMax;
	this->yMax = yMax;
}

void NBodyForce::clear()
{
	clearHelper(root);
	root = new QuadTreeNode();
}

void NBodyForce::clearHelper(QuadTreeNode *n)
{
	foreach(QuadTreeNode *i, n->children)
		if (i)
			clearHelper(i);
	delete n;
}

void NBodyForce::initialize(ForceSimulator *sim)
{
// 	qDebug() << "Initializing NBodyForce";
	clear(); // clear internal state

	// compute and squarify bounds of quadtree
	qreal x1 = std::numeric_limits<qreal>::max();
	qreal y1 = x1;
	qreal x2 = -std::numeric_limits<qreal>::max();
	qreal y2 = x2;
	foreach(ForceItem *item, sim->items())
	{
		qreal x = item->location[0];
		qreal y = item->location[1];
		if (x < x1) x1 = x;
		if (y < y1) y1 = y;
		if (x > x2) x2 = x;
		if (y > y2) y2 = y;
	}
	qreal dx = x2-x1, dy = y2-y1;
	if (dx > dy) { y2 = y1 + dx; }
	else         { x2 = x1 + dy; }
	setBounds(x1,y1,x2,y2);

	// insert items into quadtree
	foreach(ForceItem *item, sim->items())
		insert(item);

	// calculate magnitudes and centers of mass
	calcMass(root);
// 	qDebug() << "Done initializing NBodyForce";
}

void NBodyForce::insert(ForceItem *item)
{
	// insert item into the quadtrees
	insert(item, root, xMin, yMin, xMax, yMax);
}

void NBodyForce::insert(ForceItem *p, QuadTreeNode *n, qreal x1, qreal y1, qreal x2, qreal y2)
{
// 	qDebug("Inserting particle at %f,%f-%f,%f", x1,y1, x2,y2);
	// try to insert particle p at node n in the quadtree.
	// by construction, each leaf will contain either 1 or 0 particles
	if (n->hasChildren)
	{
		// n contains more than 1 particle
		insertHelper(p,n,x1,y1,x2,y2);
	}
	else if (n->value)
	{
		// n contains 1 particle
		if (isSameLocation(n->value, p))
		{
			insertHelper(p,n,x1,y1,x2,y2);
		}
		else
		{
			ForceItem *v = n->value; n->value = 0;
			insertHelper(v,n,x1,y1,x2,y2);
			insertHelper(p,n,x1,y1,x2,y2);
		}
	}
	else
	{
		// n is empty, so is a leaf
		n->value = p;
	}
}

bool NBodyForce::isSameLocation(ForceItem *f1, ForceItem *f2)
{
	qreal dx = fabs(f1->location[0]-f2->location[0]);
	qreal dy = fabs(f1->location[1]-f2->location[1]);
	return dx < 0.01 && dy < 0.01;
}

void NBodyForce::insertHelper(ForceItem *p, QuadTreeNode *n, qreal x1, qreal y1, qreal x2, qreal y2)
{
//	qDebug("Recursively inserting particle at %f,%f-%f,%f", x1,y1, x2,y2);
	qreal x = p->location[0], y = p->location[1];
	qreal splitx = (x1+x2)/2;
	qreal splity = (y1+y2)/2;
	int i = (x>=splitx ? 1 : 0) + (y>=splity ? 2 : 0);
	// create new child node, if necessary
	if (n->children[i] == 0)
	{
		n->children[i] = new QuadTreeNode();
		n->hasChildren = true;
	}
	// update bounds
	if ( i==1 || i==3 ) x1 = splitx; else x2 = splitx;
	if ( i > 1 )        y1 = splity; else y2 = splity;
	// recurse
	insert(p,n->children[i],x1,y1,x2,y2);
}

void NBodyForce::calcMass(QuadTreeNode *n)
{
	qreal xcom = 0, ycom = 0;
	n->mass = 0;
	if (n->hasChildren) {
		for (int i=0; i < n->children.size(); i++ ) {
			if (n->children[i] != 0) {
				calcMass(n->children[i]);
				n->mass += n->children[i]->mass;
				xcom += n->children[i]->mass * n->children[i]->com[0];
				ycom += n->children[i]->mass * n->children[i]->com[1];
			}
		}
	}
	if (n->value != 0) {
		n->mass += n->value->mass;
		xcom += n->value->mass * n->value->location[0];
		ycom += n->value->mass * n->value->location[1];
	}
	n->com[0] = xcom / n->mass;
	n->com[1] = ycom / n->mass;
// 	qDebug("calcMass: final node mass %f", n->mass);
}

void NBodyForce::updateForceOn(ForceItem *item)
{
// 	qDebug(__PRETTY_FUNCTION__);
	forceHelper(item,root,xMin,yMin,xMax,yMax);
}

void NBodyForce::forceHelper(ForceItem *item, QuadTreeNode *n, qreal x1, qreal y1, qreal x2, qreal y2)
{
	qreal dx = n->com[0] - item->location[0];
	qreal dy = n->com[1] - item->location[1];
	qreal r  = sqrt(dx*dx+dy*dy);
	bool same = false;
	if (r == 0.0f) {
		// if items are in the exact same place, add some noise
		//range [-0.5..0.5) / 50.0
		dx = ((qreal)random()-(RAND_MAX/2))/RAND_MAX / 50.0f;//rand.nextqreal()
		dy = ((qreal)random()-(RAND_MAX/2))/RAND_MAX / 50.0f;//rand.nextqreal()
		r  = sqrt(dx*dx+dy*dy);
		same = true;
	}
	bool minDist = params[IDX_MIN_DISTANCE]>0.0 && r>params[IDX_MIN_DISTANCE];

	// the Barnes-Hut approximation criteria is if the ratio of the
	// size of the quadtree box to the distance between the point and
	// the box's center of mass is beneath some threshold theta.
	if ((!n->hasChildren && n->value != item) ||
			(!same && (x2-x1)/r < params[IDX_BARNES_HUT_THETA]))
	{
		if (minDist) return;
		// either only 1 particle or we meet criteria
		// for Barnes-Hut approximation, so calc force
		qreal v = params[IDX_GRAVITATIONAL_CONST]*item->mass*n->mass / (r*r*r);
		item->force[0] += v*dx;
		item->force[1] += v*dy;
	} else if (n->hasChildren) {
		// recurse for more accurate calculation
		qreal splitx = (x1+x2)/2;
		qreal splity = (y1+y2)/2;
		for (int i=0; i<n->children.size(); i++) {
			if (n->children[i] != 0) {
				forceHelper(item, n->children[i],
					(i==1||i==3?splitx:x1), (i>1?splity:y1),
					(i==1||i==3?x2:splitx), (i>1?y2:splity));
			}
		}
		if (minDist) return;
		if (n->value != 0 && n->value != item) {
			qreal v = params[IDX_GRAVITATIONAL_CONST]*item->mass*n->value->mass / (r*r*r);
			item->force[0] += v*dx;
			item->force[1] += v*dy;
		}
	}
}

}

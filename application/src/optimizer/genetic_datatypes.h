#pragma once
class Geometry
{
public:
	Geometry(const Geometry &geom)
	{

	}
	Geometry(const std::string filename)
	{

	}
	~Geometry()
	{
		delete[] _points;
		_pointCount = 0;
	}
	void Load();
	void Save();
	void Normalze();
	void Transform();

private:
	Point *_points;
	int _pointCount;
};
class Point
{
public:
	Point(double xin, double yin) :
		x(xin),
		y(yin)
	{}
	Point() :
		x(0.0),
		y(0.0)
	{}

	double x, y;
};
class Genome
{
public:
	Genome(Geometry &geometry) :
		_geom(geometry)
	{}
private:
	Geometry _geom;
};
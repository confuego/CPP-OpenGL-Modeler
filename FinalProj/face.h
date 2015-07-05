#include "algebra3.h"
#include "algebra3.h"

// Simple class for hold face data
class Face{
	private:
		mat4 points;
	public:
		Face(vec3& v1,vec3& v2, vec3& v3, vec3& v4){
			points[0][0] = v1[0];
			points[1][0] = v1[1];
			points[2][0] = v1[2];
			points[0][1] = v2[0];
			points[1][1] = v2[1];
			points[2][1] = v2[2];
			points[0][2] = v3[0];
			points[1][2] = v3[1];
			points[2][2] = v3[2];
			points[0][3] = v4[0];
			points[1][3] = v4[1];
			points[2][3] = v4[2];
			points[3][0] = points[3][1] = points[3][2] = points[3][3] = 1;
		}
		const mat4 getPoints(){
			return points;
		}
		const vec3 getNormal(){
			vec3 r = -1*(points.getColumn(1)-points.getColumn(0))^(points.getColumn(2)-points.getColumn(1));
			return r/r.length();
	}
};
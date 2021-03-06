#pragma once

#include "main.h"

class CMath
{
public:
	void AngleMatrix(const Vector angles, matrix3x4_t & matrix);
	void AngleMatrix(QAngle vecAngles, Vector vecOrigin, matrix3x4_t& matrix);
	void MatrixAngles(const matrix3x4_t & matrix, float * angles);
	void MatrixAngle(const matrix3x4_t & matrix, QAngle & angles, Vector & position);
	void inline SinCos( float radians, float *sine, float *cosine );
	void CalcAngle( Vector &vIn, const Vector &vDest, Vector &vAngles );
	void VectorAngles( const Vector & forward, QAngle & angles );
	void VectorAngles( const Vector & forward, Vector & angles );
	QAngle CalcAngle( Vector src, Vector dst );
	Vector CalcAngles( Vector src, Vector dst );
	void AngleVector( Vector &vAngle, Vector &vForward );
	void AngleVector( const Vector & angles, Vector * forward, Vector * right, Vector * up );
	void AngleVector( const Vector angles, float * forward, float * right, float * up );

	float DotProduct( const float * v1, const float * v2 );
	void FloatTransform( const float * in1, const matrix3x4_t & in2, float * out );
	void VectorTransform( const Vector & in1, const matrix3x4_t & in2, Vector & out );

	Vector GetHitspot( CBaseEntity* pEntity, int iHitBox );

	Vector GetHitspot( CBaseEntity * pEntity, int iHitBox, matrix3x4_t * matrix );

	float AngleDiff(float destAngle, float srcAngle);

	void NormalizeQAngle( QAngle & vec );

	void NormalizeVector( Vector & vec );

	void ClampAngles( Vector & Vectors );

	void MakeVector( Vector vecIn, Vector & vecOut );

	float GetRageFoV( Vector angle, Vector src, Vector dst );

	float GetFoV( Vector angle, Vector src, Vector dst );

	void BulletLocation( CBaseEntity * pLocal, CBaseCombatWeapon * pWeapon, Vector & vViewAngles, Vector & vBullet );

	void FixMovement(const Vector & old_view, CUserCmd * cmd, CBaseEntity * local);

	Vector RotateMatrix(CBaseEntity * pLocal, int bone, float rotation);

	void VectorRotate(const float * in1, const matrix3x4_t & in2, float * out);

	void VectorRotate(const Vector & in1, const matrix3x4_t & in2, Vector & out);

	void VectorRotate(const Vector & in1, const Vector & in2, Vector & out);

	void MatrixMultiply(matrix3x4_t & in1, const matrix3x4_t & in2);

	matrix3x4_t MultiplyMatrix(matrix3x4_t & in1, const matrix3x4_t & in2);

	void RotateMovement( CUserCmd * pCmd, float flYaw );

	void GetSpreadFix( CBaseEntity * pLocal, UINT seed, Vector & pflInAngles, CUserCmd * pCmd );

	float RandomFloat( float a, float b ) 
	{
		float random = ( ( float )rand() ) / ( float )RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}

	inline Vector MatrixGetPosition(const matrix3x4_t& src)
	{
		return Vector(src[0][3], src[1][3], src[2][3]);
	}

	inline float SSESqrt(float x)
	{
		float root = 0.0f;

		__asm
		{
			sqrtss xmm0, x
			movss root, xmm0
		}

		return root;
	}

	float flJitter(float a, float b)
	{
		return rand() % 2 ? a : b;
	}

	int RandomInteger( int a, int b )
	{
		int random = ( rand() ) / RAND_MAX;
		int diff = b - a;
		int r = random * diff;
		return a + r;
	}

	inline float NormalizePitch( float pitch )
	{
		while( pitch > 89.f )
			pitch -= 180.f;
		while( pitch < -89.f )
			pitch += 180.f;

		return pitch;
	}

	inline float NormalizeYaw( float yaw )
	{
		if( yaw > 180 )
			yaw -= ( round( yaw / 360 ) * 360.f );
		else if( yaw < -180 )
			yaw += ( round( yaw / 360 ) * -360.f );

		return yaw;
	}

	inline float GetDistance( const Vector &start, const Vector &end )
	{
		float distance = sqrt( ( start - end ).Length() );

		if( distance < 1.0f )
			distance = 1.0f;

		return distance;
	}
	template <class T>
	constexpr const T& Min( const T& x, const T& y )
	{
		return ( x > y ) ? y : x;
	}

	template <class T>
	constexpr const T& Max( const T& x, const T& y )
	{
		return ( x < y ) ? y : x;
	}
};
extern CMath g_Math;

const double M_U_DEG = 360.0 / 65536;
const double M_U_RAD = M_PI / 32768;
#define PI_2 M_PI/2
#define PI_4 M_PI/4

class AutoStrafer
{
	double anglemod_deg( double a )
	{
		return M_U_DEG * ( ( int ) ( a / M_U_DEG ) & 0xffff );
	}

	double anglemod_rad( double a )
	{
		return M_U_RAD * ( ( int ) ( a / M_U_RAD ) & 0xffff );
	}

	double point2line_distsq( const double pos[ 2 ],
		const double line_origin[ 2 ],
		const double line_dir[ 2 ] )
	{
		double tmp[ 2 ] = { line_origin[ 0 ] - pos[ 0 ], line_origin[ 1 ] - pos[ 1 ] };
		double dotprod = line_dir[ 0 ] * tmp[ 0 ] + line_dir[ 1 ] * tmp[ 1 ];
		tmp[ 0 ] -= line_dir[ 0 ] * dotprod;
		tmp[ 1 ] -= line_dir[ 1 ] * dotprod;
		return tmp[ 0 ] * tmp[ 0 ] + tmp[ 1 ] * tmp[ 1 ];
	}

	double strafe_theta_opt( double speed, double L, double tauMA )
	{
		double tmp = L - tauMA;
		if( tmp <= 0 )
			return PI_2;
		if( tmp < speed )
			return std::acos( tmp / speed );
		return 0;
	}

	double strafe_theta_const( double speed, double nofric_speed, double L,
		double tauMA )
	{
		double sqdiff = nofric_speed * nofric_speed - speed * speed;
		double tmp = sqdiff / tauMA;
		if( tmp + tauMA < 2 * L && 2 * speed >= std::fabs( tmp - tauMA ) )
			return std::acos( ( tmp - tauMA ) / ( 2 * speed ) );
		tmp = std::sqrt( L * L - sqdiff );
		if( tauMA - L > tmp && speed >= tmp )
			return std::acos( -tmp / speed );
		return strafe_theta_opt( speed, L, tauMA );
	}

	void strafe_fme_vec( double vel[ 2 ], const double avec[ 2 ], double L,
		double tauMA )
	{
		double tmp = L - vel[ 0 ] * avec[ 0 ] - vel[ 1 ] * avec[ 1 ];
		if( tmp < 0 )
			return;
		if( tauMA < tmp )
			tmp = tauMA;
		vel[ 0 ] += avec[ 0 ] * tmp;
		vel[ 1 ] += avec[ 1 ] * tmp;
	}

	void strafe_fric( double vel[ 2 ], double E, double ktau )
	{
		double speed = std::hypot( vel[ 0 ], vel[ 1 ] );
		if( speed >= E )
		{
			vel[ 0 ] *= 1 - ktau;
			vel[ 1 ] *= 1 - ktau;
			return;
		}

		double tmp = E * ktau;
		if( speed > tmp )
		{
			tmp /= speed;
			vel[ 0 ] -= tmp * vel[ 0 ];
			vel[ 1 ] -= tmp * vel[ 1 ];
			return;
		}

		vel[ 0 ] = 0;
		vel[ 1 ] = 0;
	}

	double strafe_fric_spd( double spd, double E, double ktau )
	{
		if( spd >= E )
			return spd * ( 1 - ktau );
		double tmp = E * ktau;
		if( spd > tmp )
			return spd - tmp;
		return 0;
	}

	void strafe_side( double& yaw, int& Sdir, int& Fdir, double vel[ 2 ],
		double theta, double L, double tauMA, int dir )
	{
		double phi;
		// This is to reduce the overall shaking.
		if( theta >= PI_2 * 0.75 )
		{
			Sdir = dir;
			Fdir = 0;
			phi = std::copysign( PI_2, dir );
		}
		else if( PI_2 * 0.25 <= theta && theta <= PI_2 * 0.75 )
		{
			Sdir = dir;
			Fdir = 1;
			phi = std::copysign( PI_4, dir );
		}
		else
		{
			Sdir = 0;
			Fdir = 1;
			phi = 0;
		}

		if( std::fabs( vel[ 0 ] ) > 0.1 || std::fabs( vel[ 1 ] ) > 0.1 )
			yaw = std::atan2( vel[ 1 ], vel[ 0 ] );
		yaw += phi - std::copysign( theta, dir );
		double yawcand[ 2 ] = {
			anglemod_rad( yaw ), anglemod_rad( yaw + std::copysign( M_U_RAD, yaw ) )
		};
		double avec[ 2 ] = { std::cos( yawcand[ 0 ] - phi ), std::sin( yawcand[ 0 ] - phi ) };
		double tmpvel[ 2 ] = { vel[ 0 ], vel[ 1 ] };
		strafe_fme_vec( vel, avec, L, tauMA );
		avec[ 0 ] = std::cos( yawcand[ 1 ] - phi );
		avec[ 1 ] = std::sin( yawcand[ 1 ] - phi );
		strafe_fme_vec( tmpvel, avec, L, tauMA );

		if( tmpvel[ 0 ] * tmpvel[ 0 ] + tmpvel[ 1 ] * tmpvel[ 1 ] >
			vel[ 0 ] * vel[ 0 ] + vel[ 1 ] * vel[ 1 ] )
		{
			vel[ 0 ] = tmpvel[ 0 ];
			vel[ 1 ] = tmpvel[ 1 ];
			yaw = yawcand[ 1 ];
		}
		else
			yaw = yawcand[ 0 ];
	}

public:
	void strafe_side_opt( double& yaw, int& Sdir, int& Fdir, double* vel,
		double L, double tauMA, int dir )
	{
		double speed = std::hypot( vel[ 0 ], vel[ 1 ] );
		double theta = strafe_theta_opt( speed, L, tauMA );
		strafe_side( yaw, Sdir, Fdir, vel, theta, L, tauMA, dir );
	}

	void strafe_side_const( double& yaw, int& Sdir, int& Fdir, double vel[ 2 ],
		double nofricspd, double L, double tauMA, int dir )
	{
		double speed = std::hypot( vel[ 0 ], vel[ 1 ] );
		double theta = strafe_theta_const( speed, nofricspd, L, tauMA );
		strafe_side( yaw, Sdir, Fdir, vel, theta, L, tauMA, dir );
	}

	void strafe_line_opt( double& yaw, int& Sdir, int& Fdir, double vel[ 2 ],
		double pos[ 2 ], double L, double tau, double MA,
		double line_origin[ 2 ], double line_dir[ 2 ] )
	{
		double tauMA = tau * MA;
		double speed = std::hypot( vel[ 0 ], vel[ 1 ] );
		double theta = strafe_theta_opt( speed, L, tauMA );
		double ct = std::cos( theta );
		double tmp = L - speed * ct;
		if( tmp < 0 )
		{
			strafe_side( yaw, Sdir, Fdir, vel, theta, L, tauMA, 1 );
			return;
		}

		if( tauMA < tmp )
			tmp = tauMA;
		tmp /= speed;
		double st = std::sin( theta );
		double newpos_right[ 2 ], newpos_left[ 2 ];
		double avec[ 2 ];

		avec[ 0 ] = ( vel[ 0 ] * ct + vel[ 1 ] * st ) * tmp;
		avec[ 1 ] = ( -vel[ 0 ] * st + vel[ 1 ] * ct ) * tmp;
		newpos_right[ 0 ] = pos[ 0 ] + tau * ( vel[ 0 ] + avec[ 0 ] );
		newpos_right[ 1 ] = pos[ 1 ] + tau * ( vel[ 1 ] + avec[ 1 ] );

		avec[ 0 ] = ( vel[ 0 ] * ct - vel[ 1 ] * st ) * tmp;
		avec[ 1 ] = ( vel[ 0 ] * st + vel[ 1 ] * ct ) * tmp;
		newpos_left[ 0 ] = pos[ 0 ] + tau * ( vel[ 0 ] + avec[ 0 ] );
		newpos_left[ 1 ] = pos[ 1 ] + tau * ( vel[ 1 ] + avec[ 1 ] );

		bool rightgt = point2line_distsq( newpos_right, line_origin, line_dir ) <
			point2line_distsq( newpos_left, line_origin, line_dir );
		strafe_side( yaw, Sdir, Fdir, vel, theta, L, tauMA, rightgt ? 1 : -1 );
	}

	void strafe_back( double& yaw, int& Sdir, int& Fdir, double vel[ 2 ],
		double tauMA )
	{
		Sdir = 0;
		Fdir = -1;

		yaw = std::atan2( vel[ 1 ], vel[ 0 ] );
		float frac = yaw / M_U_RAD;
		frac -= std::trunc( frac );
		if( frac > 0.5 )
			yaw += M_U_RAD;
		else if( frac < -0.5 )
			yaw -= M_U_RAD;
		yaw = anglemod_rad( yaw );

		double avec[ 2 ] = { std::cos( yaw ), std::sin( yaw ) };
		vel[ 0 ] -= tauMA * avec[ 0 ];
		vel[ 1 ] -= tauMA * avec[ 1 ];
	}

	double strafe_opt_spd( double spd, double L, double tauMA )
	{
		double tmp = L - tauMA;
		if( tmp < 0 )
			return std::sqrt( spd * spd + L * L );
		if( tmp < spd )
			return std::sqrt( spd * spd + tauMA * ( L + tmp ) );
		return spd + tauMA;
	}
};

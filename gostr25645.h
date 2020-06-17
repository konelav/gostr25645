#ifndef _GOST_R_25645_H_INCLUDED
#define _GOST_R_25645_H_INCLUDED

/*
 * GOST R 25645.166-2004
 * Earth upper atmosphere
 * Density model for ballistic support of flights of artificial earth satellites
 * http://docs.cntd.ru/document/gost-r-25645-166-2004
 */

/* 
 * Solar flux and geomagnetic data:
 * ftp://ftp.swpc.noaa.gov/pub/indices/
 */

/* Returned value: atmospheric density in [kg/m^3] */
double rho_gostr25645(
    double F10_7,           /* Solar flux at 10.7 cm (delayed by SOLAR_DT) [1e-22 W/m^2/Hz] */
    double F81,             /* Mean solar flux at 10.7 cm in last 81 days [1e-22 W/m^2/Hz] */
    double Kp,              /* Geomagnetic daily index (delayed by GEOM_DT) [unitless] */
    double doy,             /* Day of year, fractions allowed [days] */
    double sod,             /* Seconds of day [sec] */
    double gst_midnight,    /* Greenwich sidereal time at midnight [rad] */
    double x,               /* 'Greenwich' (ECEF) X coordinate of point [km] */
    double y,               /* 'Greenwich' (ECEF) Y coordinate of point [km] */
    double z,               /* 'Greenwich' (ECEF) Z coordinate of point [km] */
    double h,               /* Geodetic altitude (height above ellipsoid) of point,
                               should be not less than 120.0 [km] */
    double sun_ra,          /* Right ascension of the Sun [rad] */
    double sun_de           /* Declination of the Sun [rad] */
);
/*
 * Note 1: fraction of `doy` and value of `sod` can contradict each other, no check
 *         will be made; `doy` is used only for solar/geomegnetic estimations, while
 *         `sod` is used only for calculating angles relative to Sun position
 * 
 * Note 2: `x`, `y`, `z` actually can have any unit (only their relations matter)
 * 
 * Note 3: for using ECI reference frame one should provide along with ECI `x`, `y` and `z`
 *         zeroed values for `sod` and `gst_midnight`
 * 
 * Note 4: values of `x`, `y`, `z` and `h` can contradict each other
 * 
 * Note 5: no errors will be indicated on ill inputs
 */

void prepare_gostr25645(
    const double *hjd,      /* Timestamps in form of fractional Julian Dates of measurements.
                               It is strongly recommended to provide data for at least 81 days [days] */
    const double *hF10_7,   /* Measurements of solar flux at 10.7 cm [1e-22 W/m^2/Hz] */
    const double *hKp,      /* Measurements of daily geomagnetic index [unitless] */
    int hsize,              /* Number of entries in arrays `hjd`, `hF10_7` and `hKp` [unitless] */
    double jd,              /* Julian date for calculating outputs [days] */
    
    double *F10_7,          /* Inter-/extrapolated value for solar flux at 10.7 cm,
                               delayed by SOLAR_DT [1e-22 W/m^2/Hz] */
    double *F81,            /* Mean solar flux at 10.7 cm in last 81 days (or less
                               if not enough data was provided) [1e-22 W/m^2/Hz] */
    double *Kp              /* Inter-/extrapolated value for geomagnetic daily index,
                               delayed by GEOM_DT [unitless] */
);
/*
 * Note 1: `hjd[]` and `jd` actually can have any unit (only their relations matter)
 * 
 * Note 2: values in `hjd[]` must be in strictly ascending order
 * 
 * Note 3: no errors will be indicated on ill inputs e.g. hsize <= 0 or
 *         `jd` far from the range of `hjd[]`
 */
#endif /* _GOST_R_25645_H_INCLUDED */

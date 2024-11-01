import math
from datetime import datetime, timedelta
import ephem


def calculate_solar_position(latitude, longitude, date):
    """
    Calculate solar position for a given location and date
    Returns altitude and azimuth in degrees
    """
    observer = ephem.Observer()
    observer.lat = str(latitude)
    observer.lon = str(longitude)
    observer.date = date

    sun = ephem.Sun()
    sun.compute(observer)

    # Convert to degrees from radians
    altitude = math.degrees(float(sun.alt))
    azimuth = math.degrees(float(sun.az))

    return altitude, azimuth


def calculate_shadow_length(object_height, solar_altitude):
    """
    Calculate shadow length based on object height and sun's altitude
    """
    altitude_rad = math.radians(solar_altitude)
    shadow_length = object_height / math.tan(altitude_rad)
    return shadow_length


def calculate_attachment_height(theta, altitude):
    return (math.sin(math.radians(altitude) - math.radians(theta)) * 5.5) / (
        math.sin(math.pi / 2 - math.radians(altitude))
    )


def design_pyramid_projection(base_width, height, latitude, longitude):
    """
    Calculate projection dimensions for summer solstice shadows
    """
    # Get summer solstice date for current year
    year = datetime.now().year
    solstice_date = ephem.next_summer_solstice(ephem.now())
    theta = math.atan(3)

    # Calculate solar positions throughout solstice day
    times = []
    altitudes = []
    azimuths = []
    shadow_lengths = []
    attachment_heights = []

    for hour in range(24):
        for minute in range(0, 60, 15):  # Check every 15 minutes
            time = ephem.Date(solstice_date) + hour * ephem.hour + minute * ephem.minute
            alt, az = calculate_solar_position(latitude, longitude, time)

            if alt > 0:  # Only include daylight hours
                times.append(time)
                altitudes.append(alt)
                azimuths.append(az)
                shadow_lengths.append(calculate_shadow_length(height, alt))
                attachment_heights.append(calculate_attachment_height(theta, alt))

    # Calculate projection dimensions
    min_shadow = min(shadow_lengths)
    max_shadow = max(shadow_lengths)
    midday_alt, midday_az = calculate_solar_position(
        latitude, longitude, ephem.Date(solstice_date) + 12 * ephem.hour
    )

    midday_attachment = calculate_attachment_height(
        theta,
        calculate_solar_position(
            latitude, longitude, ephem.Date(solstice_date) + 12 * ephem.hour
        )[0],
    )

    return {
        "min_shadow_length": min_shadow,
        "max_shadow_length": max_shadow,
        "min_attachment_height": min(attachment_heights),
        "max_attachment_height": max(attachment_heights),
        "projection_length": max_shadow - min_shadow,
        "recommended_projection_depth": (max_shadow - min_shadow)
        * 0.1,  # 10% of shadow difference
        "solar_altitude_range": (min(altitudes), max(altitudes)),
        "solar_azimuth_range": (min(azimuths), max(azimuths)),
        "midday_attachment_height": midday_attachment,
        "midday_azimuth": midday_az,
        "midday_altitude": midday_alt,
    }


if __name__ == "__main__":
    LATITUDE = 43.471141
    LONGITUDE = -80.548022
    PYRAMID_HEIGHT = 7.5  # meters
    BASE_WIDTH = 5  # meters

    results = design_pyramid_projection(BASE_WIDTH, PYRAMID_HEIGHT, LATITUDE, LONGITUDE)
    print("Pyramid Projection Design Parameters:")

    for key, value in results.items():
        print(f"{key}: {value}")

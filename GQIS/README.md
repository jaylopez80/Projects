Vegetation Change & Climate Stress in the Sierra Nevada
Author: Jonathan Lopez
Institution: Chapman University
Course: Computer Science / Data Science
Year: 2024

Overview
This project analyzes vegetation health and climate stress across the Sierra Nevada mountain range using satellite-derived NDVI (Normalized Difference Vegetation Index) data combined with climate projections from Cal-Adapt. The goal was to quantify how vegetation responds to seasonal temperature and precipitation patterns, and to identify spatial and temporal trends that may indicate climate-driven stress on Sierra Nevada forests.
Forests in this region serve as major carbon sinks, storing CO2 in biomass. Increasing drought, extreme heat events, and wildfires are reducing the recovery capacity of these ecosystems. This project uses remote sensing and Python-based analysis to measure that impact using real 2024 data.

Research Objectives

Quantify vegetation health across the Sierra Nevada using MODIS NDVI data for 2024
Analyze seasonal NDVI trends and identify temporal patterns throughout the year
Compare NDVI values against temperature and precipitation data from Cal-Adapt climate models
Apply machine learning clustering to identify seasonal vegetation groups and their climate relationships


Data Sources
MODIS NDVI

Dataset: MODIS MOD13Q1 — 250 meter resolution, 16-day NDVI composite
Source: NASA EarthData (https://earthdata.nasa.gov)
Coverage: 2024 tiles covering the Sierra Nevada region
Index: NDVI values scaled from -1 to +1, where higher values indicate denser, healthier vegetation

Climate Data

Source: Cal-Adapt (https://cal-adapt.org)
Model: SSP3-7.0 ACCESS-CM2 climate scenario
Variables: Monthly maximum temperature (tasmax), minimum temperature (tasmin), and precipitation (pr_mm_day)
Coverage: 2024, aligned to Sierra Nevada boundary


GIS Processing Workflow (QGIS)
All spatial preprocessing was performed in QGIS before Python analysis.
Steps Performed in QGIS

Downloaded MODIS tiles from NASA EarthData covering the Sierra Nevada geographic extent for the full year 2024
Clipped rasters to Sierra Nevada boundary — imported a Sierra Nevada region shapefile and used the Clip Raster by Mask Layer tool to isolate only the study area, removing surrounding regions from analysis
Reprojected to EPSG:3310 — California Albers Equal Area projection was applied to all rasters to ensure consistent spatial measurements across the study area. This projection is standard for California-wide environmental analysis
Applied consistent NDVI color ramp — a standardized color ramp (dark purple for low/negative NDVI to bright yellow-green for high NDVI) was applied across all time period rasters to allow direct visual comparison between seasons
Exported GeoTIFFs — processed rasters were exported as GeoTIFF files for ingestion into Python for quantitative analysis

Key QGIS Tools Used

Clip Raster by Mask Layer
Warp (Reproject)
Raster Layer Properties / Symbology (color ramp standardization)
Export / Save As (GeoTIFF format)


Python Analysis
All quantitative analysis was performed in Python using the following libraries:
LibraryPurposerioxarrayReading and processing GeoTIFF raster filespandasTabular data management and time series organizationmatplotlibData visualization and plot generationsklearnK-Means clustering for seasonal pattern identification
Analysis Steps

NDVI Conversion — raw MODIS scale values converted to standard reflectance (-1 to +1 scale)
Mean NDVI Computation — calculated mean NDVI per 16-day composite across the Sierra Nevada extent
Monthly Aggregation — composites aggregated to monthly means for temporal trend analysis
Climate Variable Integration — Cal-Adapt temperature and precipitation data aligned to the same monthly timeline
Regression Analysis — NDVI values regressed against max temperature and precipitation to identify climate relationships
K-Means Clustering — unsupervised clustering applied to group months by NDVI and temperature profiles, identifying seasonal vegetation behavior patterns


Key Findings

Seasonal NDVI pattern peaks in late spring through summer (May–July, NDVI ~0.44) and drops sharply in late fall and winter (Feb lowest at ~0.30), consistent with snowmelt-driven growing seasons
NDVI seasonality closely tracks temperature and precipitation cycles — vegetation greenness rises as temperatures warm and then persists through the dry summer due to residual snowmelt moisture
A slight upward NDVI trend in 2024 suggests some degree of vegetation recovery, possibly reflecting above-average precipitation earlier in the year
Results confirm a Mediterranean-type growth pattern — vegetation responds strongly to rainfall events and shows stress during dry summer months despite warm temperatures
K-Means clustering separated months into distinct seasonal groups: cool/dormant (Nov–Mar), transitional (Apr), and active growing season (May–Oct), each with distinct NDVI-temperature signatures


Spatial Results

January–March: Lower NDVI values across most of the Sierra Nevada, with higher elevation zones showing near-zero or negative values due to snow cover
June–August: Strong vegetation signal concentrated along the western Sierra slopes, with the highest NDVI values in mid-elevation forested zones


Future Extensions

Extend analysis to multi-year Cal-Adapt climate trends to detect longer-term vegetation decline
Integrate historical wildfire perimeter data to correlate burn areas with post-fire NDVI recovery rates
Incorporate soil moisture indices to better explain summer NDVI maintenance during dry periods
Expand spatial resolution using Landsat or Sentinel-2 data for finer-scale analysis

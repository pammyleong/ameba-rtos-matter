/*
 *
 *    Copyright (c) 2023 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <matter_air_quality_instance.h>

using namespace chip::app::Clusters;
using namespace chip::app::Clusters::AirQuality;

Instance * gAirQualityCluster = nullptr;

Instance * AirQuality::GetInstance()
{
    return gAirQualityCluster;
}

void AirQuality::Shutdown()
{
    if (gAirQualityCluster != nullptr)
    {
        delete gAirQualityCluster;
        gAirQualityCluster = nullptr;
    }
}

void emberAfAirQualityClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(endpointId == 1); // this cluster is only enabled for endpoint 1.
    VerifyOrDie(gAirQualityCluster == nullptr);
    chip::BitMask<Feature, uint32_t> airQualityFeatures(Feature::kModerate, Feature::kFair, Feature::kVeryPoor,
                                                        Feature::kExtremelyPoor);
    gAirQualityCluster = new Instance(1, airQualityFeatures);
    gAirQualityCluster->Init();
}

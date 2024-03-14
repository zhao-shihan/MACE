SmearMACE $1 \
    --cdc-hit tD 'gRandom->Gaus(tD, 0.2/0.035*sqrt(tD/(5/0.035)))' \
    --cdc-hit t 'gRandom->Gaus(t, 30)' \
    --cdc-hit d 'gRandom->Gaus(d, 0.2*sqrt(d/5))' \
    --cdc-track-id \
    --emc-hit t 'gRandom->Gaus(t, 150)' \
    --emc-hit Edep 'gRandom->Gaus(Edep, 1e-3*(8.123+7.912e-2*sqrt(1e3*Edep-0.2445*Edep*Edep)))' \
    --mcp-hit t 'gRandom->Gaus(t, 0.05)'

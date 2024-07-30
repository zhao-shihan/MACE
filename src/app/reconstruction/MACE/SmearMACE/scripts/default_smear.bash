SmearMACE $1 \
    --cdc-hit tD 'Gauss(x, 0.2/0.035*sqrt(x/(5/0.035)))' \
    --cdc-hit t 'Gauss(x, 30)' \
    --cdc-hit d 'Gauss(x, 0.2*sqrt(x/5))' \
    --ttc-hit t 'Gauss(x, 0.05)' \
    --mms-track-id \
    --emc-hit t 'Gauss(x, 150)' \
    --emc-hit Edep 'Gauss(x, 1e-3*(8.123+7.912e-2*sqrt(1e3*x-0.2445*x*x)))' \
    --mcp-hit t 'Gauss(x, 0.5)'

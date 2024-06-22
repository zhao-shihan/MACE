import yaml

for i in range(5, 16):
    for j in range(15, 26):
        test = {
            "EMC": {
                "InnerRadius": j * 10,
                "CrystalHypotenuse": i * 1.86 * 10,
                "UpstreamWindowRadius":0,
                "DownstreamWindowRadius":0,
            }
        }

        with open("test_{}X0_{}.yaml".format(i, j), "w") as f:
            yaml.safe_dump(test, f)

        # 生成.mac文件名和yaml文件名
        mac_filename = "test_{}X0_{}.mac".format(i, j)
        yaml_filename = "test_{}X0_{}.yaml".format(i, j)
        root_filename = "test_{}X0_{}".format(i, j)

        # 写入mac文件内容
        with open(mac_filename, "w") as f:
            f.write(f"""/control/verbose 0
//run/verbose 0
/event/verbose 0
/tracking/verbose 0

/MACE/Physics/UseOpticalPhysics
/Mustard/Detector/Description/Import {yaml_filename}

/run/initialize

/MACE/Generator/SwitchToGPSX

/gps/particle gamma
/gps/ene/mono 0.511 MeV
/gps/pos/centre 0. 0. 0. cm
/gps/direction -0.231259 0.883817 -0.386541

/MACE/Analysis/FilePath {root_filename}
/MACE/Analysis/FileMode RECREATE
/run/beamOn 10000
/MPIRun/PrintRunSummary
""")

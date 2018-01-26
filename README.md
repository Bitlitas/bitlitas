# Bitlitas

Lietuviška kriptovaliuta

* Reikia *

cmake build-essential pkg-config libboost-all-dev libssl-dev libzmq3-dev libsodium-dev libreadline6-dev git

* Diegimas *

git clone https://github.com/Bitlitas/bitlitas.git

cd bitlitas

make (arba make -j1 su vienų core jei mažai ramų)

cd build/release/bin

./bitlitasd

Daugiau informacijos: --help

* Nauja piniginė *

Veikiant jungčiai piniginė yra bitlitas-wallet-cli failas

Rašome norėdami susikurti naują piniginę:
 ./bitlitas-wallet-cli --generate-new-wallet=piniginesPavadinimas.bin

Atverti jau sukurtą:
./bitlitas-wallet-cli --walelt=piniginesPavadinimas.bin

Norėdami pradėti kasti, rašome start_mining [branduolių skaičius]

Daugiau informacijos: --help

Nepamirškite išsisaugoti žodžių paslapties ir rakto.
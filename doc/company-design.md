
### Strategy:

+ Choose one depo of Packeta company and make a model of its logistics (Žilina, Strečno)
    - Use electric cars
    - Use autonomous cars
    - Use normal cars
    - Compare


### Required information:

+ **abilities of autonomous cars:**
    + the cost of operating an electric car
    + max load (in packages - how many packages it is able to delever in one charge)
    + max range
    + charging time
+ **abilities of electric cars (inpirated by Peugeot boxer):**
    + the cost of operating an electric car [0.3547kWh/100km](https://www.peugeot.cz/modelova-rada/boxer-furgon.html)
    + max range (loaded) [212km](https://www.peugeot.cz/modelova-rada/boxer-furgon.html)
    + max load (not needed) [15 $m^3$] [100 adresa, 2500 Z-Box] TODO: popularity of Z-Boxes, make average of packages
    + charging time (not needed - bcs. it will charge outside of working hours)
+ **abilities of normal cars (inpirated by Peugeot boxer):**
    + the cost of operating a normal car [8,8 l/100km](https://www.peugeot.cz/modelova-rada/boxer-furgon.html)
    + max load same as electric cars
+ the cost of the courier [1600€-2000€/month](https://www.profesia.sk/praca/packeta-slovakia/O4706942)
+ popularity of Z-Boxes vs other delivery kinds [20% popularity for boxes](https://komoraplus.cz/2023/09/21/nad-boxy-stale-jasne-vede-doruceni-domu/)
+ Number of packages that courier can deliver per day [100 to address, 2500 to boxes](https://www.forbes.sk/packeta-slovakia-dorucila-medzirocne-o-36-percent-viac-zasielok-ludia-si-oblubili-najma-z-boxy/), [44% populatiry for to address delivery, 35% popularity for pick-up-points, 21% popularity for boxes](https://komoraplus.cz/2023/09/21/nad-boxy-stale-jasne-vede-doruceni-domu/) => result will be around 1374 packages per day ($100×0,44+2300*0,35+2500×0,21$)
+ Average delivery distances for "long" (only normal cars)
+ Average delivery distances for "short" (electric cars + autonomous cars) 
+ Time for autonomous cars  delivery


### Variables:

+ Number of simulating days
+ Number of packages for delivery per day
+ Number of gas cars
+ Number of electric cars
+ Number of autonomous cars


### Thesis:

+ What is the optimal ratio of normal, electric, and autonomous cars for packet delivery? What financial savings can be realized when using a different ratio of normal, electric, and autonomous cars?

### Experiments:

+ Test different number of packages for differents ratio of elecrtic, autonomus and normal cars. Find the optimal ratio for effectivnes and many save.
+ Change ratio of delivering to parcel lockers, pick-up-places and to addres (make thesis that in a future there will be more parcel lockers and they will be more popular, bcs. they will be accessible for more people) They make the same experiments again.


# Design of the choosen company

Parcels are delivered from the designated depot daily. The quantity of parcels slated for delivery each day follows a normal distribution centered around A. These parcels are categorized into two distinct groups. The initial group contains parcels necessitating delivery beyond the operational range of electric or autonomous vehicles, constituting 2-8% of the entire parcel volume. The average distance covered for deliveries in this group spans D-E kilometers. The cost of operating a conventional combustion engine vehicle, employed by the company, stands at L€ per month.
The second group, constituting 98-92% of the parcels, encompasses those amenable to delivery through all available means. The average distance covered for deliveries in this category ranges from F-G kilometers. Each courier is equipped to handle B-C parcels, inclusive of loading, transportation, and unloading, within their 8-hour work shift. Couriers utilizing electric cars recharge their vehicles overnight at the depot, ensuring they are ready for the next day's deliveries. The cost of operating an electric car is denoted as K€ per day.
Upon completion of their work hours, couriers leave and return the subsequent day. The courier's salary, ranging from 80-100€ per day, is counted into the daily operational costs for both electric and conventional vehicles. Autonomous vehicles exclusively rely on electricity and require charging. Nevertheless, they are capable of delivering parcels throughout the day. It is assumed that during the night, autonomous vehicles either charge or deliver parcels to designated parcel lockers. Consequently, parcels destined for pick-up-places and specific addresses receive priority.
An autonomous car possesses an average transport capacity of M packages per battery charge, and the average delivery time for parcels ranges from X to Y hours.
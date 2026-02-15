from enum import IntEnum

class SetFlags(IntEnum):
    POS = 1
    CAM = 2

HUNDO_SAVES = [
    {
        'name': 'goats 1',
        'description': 'Goat herding 1',
        'filename': 'goats',
    },
    {
        'name': 'ordon gate clip',
        'description': 'Gate Clip outside Ordon Spring',
        'filename': 'ordon_gate_clip',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (400.0, 307.5, -11270.2),
        'angle': 32768,
        'cam': {
            'center': (833.467468, 477.604675, -4241.97266),
            'eye': (827.497559, 329.622986, -4532.90723)
        },
    },
    {
        'name': 'goats 2',
        'description': 'Goat herding 2',
        'filename': 'goats_2',
    },
    {
        'name': 'faron twilight',
        'description': 'Faron Twilight tears',
        'filename': 'faron_twilight',
    },
    {
        'name': 'early master sword',
        'description': 'Super Jump to Sacred Grove',
        'filename': 'ems',
    },
    {
        'name': 'purple mist',
        'description': 'Purple mist in Faron Woods (post-EMS)',
        'filename': 'purple_mist',
        'setflags': SetFlags.POS,
        'pos': (-23524.6152, 250.0, -16220.166),
        'angle': 40758,
    },
    {
        'name': 'forest bit',
        'description': 'Back in Time in Forest Temple',
        'filename': 'forest_bit',
    },
    {
        'name': 'forest temple 2',
        'description': 'The Forest Temple segment after boomerang',
        'filename': 'forest_2',
    },
    {
        'name': 'diababa',
        'description': 'Forest Temple boss',
        'filename': 'ookless',
    },
    {
        'name': 'eldin twilight',
        'description': 'Eldin Twilight tears',
        'filename': 'eldin_twilight',
    },
    {
        'name': 'bomb house skip',
        'description': 'Kakariko Bomb House Skip',
        'filename': 'bomb_house_skip',
    },
    {
        'name': 'lanayru gate clip',
        'description': 'Gate Clip to Lanayru',
        'filename': 'lanayru_gate_clip',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (-63026.2852, -9065.92578, 71680.3438),
        'angle': 44248,
        'cam': {
            'center': (-62655.8125, -8900.91309, 71903.6328),
            'eye': (-63064.2148, -8969.97656, 71661.0781)
        },
    },
    {
        'name': 'pillar clip',
        'description': 'Pillar Clip in Lake Hylia (low water)',
        'filename': 'pillar_clip',
    },
    {
        'name': 'lakebed 1',
        'description': 'The 1st Lakebed Temple segment',
        'filename': 'lakebed_1',
    },
    {
        'name': 'deku toad',
        'description': 'Lakebed Temple miniboss',
        'filename': 'deku_toad',
    },
    {
        'name': 'kargorok flight',
        'description': 'Clip OoB with trumpet bird',
        'filename': 'karg',
    },
    {
        'name': 'lanayru twilight',
        'description': 'Lanayru Twilight tears',
        'filename': 'lanayru_twilight',
    },
    {
        'name': 'coro td',
        'description': 'Text Displacement with Coro',
        'filename': 'corotd',
        'setflags': SetFlags.POS,
        'pos': (-13715.0712, 0.00, -14238.0654),
        'angle': 27714,
    },
    {
        'name': 'early ele',
        'description': 'OoB LJA to Death Mountain Elevator',
        'filename': 'early_ele',
        'setflags': SetFlags.POS,
        'pos': (1197.00, -355.55, -5468.84),
        'angle': 45137,
    },
    {
        'name': 'goron mines',
        'description': 'The Goron Mines segment',
        'filename': 'gm',
    },
    {
        'name': 'dangoro',
        'description': 'Goron Mines miniboss',
        'filename': 'dangoro',
    },
    {
        'name': 'fyrus',
        'description': 'Goron Mines boss',
        'filename': 'fyrus',
    },
    {
        'name': 'waterfall sidehop',
        'description': 'Waterfall sidehop after Rutela skip',
        'filename': 'waterfall_sidehop',
    },
    {
        'name': 'boss bug',
        'description': 'Lanayru Twilight boss bug',
        'filename': 'boss_bug',
        'setflags': SetFlags.POS,
        'pos': (-89100.00, -18811.2363, 39410.00),
        'angle': 21504,
    },
    {
        'name': 'kb2 skip',
        'description': 'Clip to skip King Bulblin 2',
        'filename': 'kb2',
        'setflags': SetFlags.CAM,
        'angle': 14957,
        'cam': {
            'center': (-92795.1328, -5302.87988, 22505.3359),
            'eye': (-92098.1797, -5398.54883, 22599.9102)
        },
    },
    {
        'name': 'wagon escort',
        'description': 'Telma wagon escort',
        'filename': 'kb2',
    },
    {
        'name': 'eldin collection',
        'description': 'Eldin Field collection segment',
        'filename': 'eldin_collection',
    },
    {
        'name': 'lakebed bk skip',
        'description': 'Boss Key skip in Lakebed Temple',
        'filename': 'lakebed_bk_skip',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (71.9835968, 1500.00, 2839.01587),
        'angle': 32767,
        'cam': {
            'center': (71.9835968, 1719.93542, 2969.04565),
            'eye': (71.9835968, 1660.0, 2839.01587)
        },
    },
    {
        'name': 'morpheel',
        'description': 'Lakebed Temple boss',
        'filename': 'morpheel',
    },
    {
        'name': 'mdh tower',
        'description': 'MDH tower climb',
        'filename': 'mdh_tower',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (25254.6875, -3031.50854, 10222.1445),
        'angle': 32025,
        'cam': {
            'center': (10193.6064, 25254.7852, -2874.2627),
            'eye': (25256.7285, -2919.95215, 2839.01587)
        },
    },
    {
        'name': 'mdh bridge',
        'description': 'MDH castle rooftops',
        'filename': 'mdh_bridge',
    },
    {
        'name': 'post mdh',
        'description': 'Collection cycle after MDH',
        'filename': 'post_mdh',
    },
    {
        'name': 'star 1',
        'description': 'The 1st STAR minigame',
        'filename': 'star_1',
    },
    {
        'name': 'kb1',
        'description': 'King Bulblin 1 fight',
        'filename': 'kb1',
    },
    {
        'name': 'iza 1 skip',
        'description': 'Plumm OoB to skip iza 1',
        'filename': 'iza_1_skip',
    },
    {
        'name': 'lake hylia cave',
        'description': 'Lake Hylia dark cave',
        'filename': 'lh_cave',
    },
    {
        'name': 'bulblin camp',
        'description': 'The camp before Arbiter\'s Grounds',
        'filename': 'camp',
    },
    {
        'name': 'arbiter\'s grounds',
        'description': 'The Arbiter\'s Grounds segment',
        'filename': 'ag',
    },
    {
        'name': 'poe 1 skip',
        'description': 'The pillar jump in Arbiter\'s Grounds',
        'filename': 'poe_1_skip',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (-2046.97168, 0.0, -587.304871),
        'angle': 49030,
        'cam': {
            'center': (-1779.00293, 213.707397, -584.686768),
            'eye': (-2047.97168, 130.16568, -587.317139)
        },
    },
    {
        'name': 'death sword',
        'description': 'Arbiter\'s Grounds miniboss',
        'filename': 'death_sword_skip',
    },
    {
        'name': 'stallord',
        'description': 'Arbiter\'s Grounds boss',
        'filename': 'stallord',
    },
    {
        'name': 'post ag',
        'description': 'Collection cycle after Arbiter\'s',
        'filename': 'post_ag',
    },
    {
        'name': 'snowpeak',
        'description': 'The Snowpeak Ruins segment',
        'filename': 'spr',
    },
    {
        'name': 'darkhammer',
        'description': 'Snowpeak Ruins miniboss',
        'filename': 'darkhammer',
    },
    {
        'name': 'spr 2',
        'description': 'The 2nd half of Snowpeak Ruins',
        'filename': 'spr_2',
    },
    {
        'name': 'spr bk lja',
        'description': 'LJA to Snowpeak Boss Key room',
        'filename': 'spr_bk_lja',
        'setflags': SetFlags.POS,
        'pos': (-2171.19, 973.96, -2384.89),
        'angle': 32887,
    },
    {
        'name': 'spr bk room',
        'description': 'Snowpeak Boss Key room',
        'filename': 'spr_bk',
    },
    {
        'name': 'blizzeta',
        'description': 'Snowpeak Ruins boss',
        'filename': 'blizzeta',
    },
    {
        'name': 'faron boost',
        'description': 'Bomb boost to Sacred Grove',
        'filename': 'nf_bomb_boost',
    },
    {
        'name': 'grove skip',
        'description': 'Grove 2 skip w/ Moon Boots',
        'filename': 'grove_skip',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (-9966.6689, 2000.0, 4085.1082),
        'angle': 22306,
        'cam': {
            'center': (-10415.2363, 2212.92139, 4370.72852),
            'eye': (-9965.82617, 2176.59863, 4084.57056)
        },
    },
    {
        'name': 'grove boost',
        'description': 'Boost to upper floor of Grove',
        'filename': 'grove_boost',
    },
    {
        'name': 'temple of time',
        'description': 'The Temple of Time segment',
        'filename': 'tot',
    },
    {
        'name': 'tot early poe',
        'description': 'Early poe 1 in Temple of Time',
        'filename': 'tot_early_poe',
        'setflags': SetFlags.POS,
        'pos': (-2462.85, 2750.0, -7.10),
        'angle': 49299,
    },
    {
        'name': 'tot statue throws',
        'description': 'Temple of Time statue throws',
        'filename': 'tot_statue_throws',
    },
    {
        'name': 'tot early hp',
        'description': 'Boost to heart piece in Temple of Time',
        'filename': 'tot_early_hp',
        'setflags': SetFlags.POS,
        'pos': (-6626, 5250, -5587),
        'angle': 0,
    },
    {
        'name': 'tot darknut',
        'description': 'Temple of Time miniboss',
        'filename': 'tot_darknut',
    },
    {
        'name': 'dot skip',
        'description': 'Door of Time skip',
        'filename': 'dot_skip',
    },
    {
        'name': 'post tot',
        'description': 'Collection cycle after Temple of Time',
        'filename': 'post_tot',
    },
    {
        'name': 'hotspring minigame',
        'description': 'Goron hotspring water minigame',
        'filename': 'hotspring',
    },
    {
        'name': 'gorge arc',
        'description': 'Gorge / South Faron collection',
        'filename': 'gorge_arc',
    },
    {
        'name': 'silver rupee',
        'description': 'Getting the Kakariko Silver Rupee',
        'filename': 'silver_rupee',
    },
    {
        'name': 'ice puzzle',
        'description': 'The Ice Puzzle segment',
        'filename': 'ice_puzzle',
    },
    {
        'name': 'iza 2',
        'description': 'Iza River Ride minigame',
        'filename': 'iza_2',
    },
    {
        'name': 'hugo archery',
        'description': 'Archery in Hidden Village',
        'filename': 'hv_archery',
        'setflags': SetFlags.POS,
        'pos': (3125.57, -62.16, -9360.22),
        'angle': 64520,
    },
    {
        'name': 'city 1',
        'description': 'The 1st City in the Sky segment',
        'filename': 'cits_1',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (1309.60645, -240.0, 5533.43848),
        'angle': 16384,
        'cam': {
            'center': (1027.53259, -108.096123, 5605.23047),
            'eye': (1313.54285, -234.203003, 5545.16846)
        },
    },
    {
        'name': 'city gate clip',
        'description': 'Clip through gate before Aeralfos',
        'filename': 'city_gate_clip',
        'setflags': SetFlags.POS,
        'pos': (16516.6094, 0, -12722.480),
        'angle': 16384,
    },
    {
        'name': 'aeralfos skip',
        'description': 'the city in the sky miniboss',
        'filename': 'aeralfos_skip',
    },
    {
        'name': 'city 2',
        'description': 'The 2nd City in the Sky segment',
        'filename': 'cits_2',
    },
    {
        'name': 'early poe cycle',
        'description': 'City early poe cycle segment',
        'filename': 'cits_poe_cycle',
        'setflags': SetFlags.POS,
        'pos': (-13990.0, 3000.0, -16200.0),
        'angle': 0,
    },
    {
        'name': 'fan tower',
        'description': 'Final fan room in City',
        'filename': 'fan_tower',
    },
    {
        'name': 'argorok',
        'description': 'City in the Sky boss',
        'filename': 'argorok',
    },
    {
        'name': 'star 2',
        'description': 'The 2nd STAR minigame',
        'filename': 'star_2',
    },
    {
        'name': 'palace 1',
        'description': 'The 1st Palace of Twilight segment',
        'filename': 'palace_1',
    },
    {
        'name': 'palace 2',
        'description': 'The 2nd Palace of Twilight segment',
        'filename': 'palace_2',
    },
    {
        'name': 'early platform cycle',
        'description': 'Early platform in Palace of Twilight',
        'filename': 'early_platform',
    },
    {
        'name': 'zant',
        'description': 'Palace of Twilight boss',
        'filename': 'zant',
    },
    {
        'name': 'cave of ordeals',
        'description': 'The Cave of Ordeals segment',
        'filename': 'coo',
    },
    {
        'name': 'coo floor 10',
        'description': 'Cave of Ordeals floor 10',
        'filename': 'coo_10',
    },
    {
        'name': 'coo floor 20',
        'description': 'Cave of Ordeals floor 20',
        'filename': 'coo_20',
    },
    {
        'name': 'coo floor 30',
        'description': 'Cave of Ordeals floor 30',
        'filename': 'coo_30',
    },
    {
        'name': 'coo floor 40',
        'description': 'Cave of Ordeals floor 40',
        'filename': 'coo_40',
    },
    {
        'name': 'cats minigame',
        'description': 'Hidden Village cats minigame',
        'filename': 'cats',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (5238.59, 0.00, -3575.74),
        'angle': 17282,
        'cam': {
            'center': (4893.25391, 160.117676, -3524.51245),
            'eye': (5309.32373, 160.1, -3581.83423)
        },
    },
    {
        'name': 'hyrule castle',
        'description': 'The Hyrule Castle segment',
        'filename': 'hc',
    },
    {
        'name': 'darknut skip',
        'description': 'Hyrule Castle 1st Darknut skip',
        'filename': 'hc_darknut',
    },
    {
        'name': 'final tower',
        'description': 'The tower climb before Ganondorf',
        'filename': 'hc_tower',
    },
    {
        'name': 'beast ganon',
        'description': 'The Beast Ganon fight',
        'filename': 'beast_ganon',
    },
    {
        'name': 'horseback ganon',
        'description': 'The Horseback Ganondorf fight',
        'filename': 'horseback_ganon',
    },
]

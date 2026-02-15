from enum import IntEnum

class SetFlags(IntEnum):
    POS = 1
    CAM = 2

ALL_DUNGEONS_SAVES = [
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
        'name': 'back in time',
        'description': 'Back in Time off the Ordon Spring bridge',
        'filename': 'ordon_gate_clip',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (466.622467, 319.770752, -11651.3867),
        'angle': 52540,
        'cam': {
            'center': (735.525391, 524.418701, -11576.4746),
            'eye': (465.674622, 421.052704, -11651.0684)
        },
    },
    {
        'name': 'goats',
        'description': 'Goat herding 2',
        'filename': 'goats',
    },
    {
        'name': 'sword and shield skip',
        'description': 'Hangin\' with Hugo',
        'filename': 'hugo',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (2.9385, 396.9580, -18150.087),
        'angle': 40166,
        'cam': {
            'center': (735.525391, 524.418701, -11576.4746),
            'eye': (465.674622, 421.052704, -11651.0684)
        },
    },
    {
        'name': 'faron twilight',
        'description': 'Faron Twilight 1st half',
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
        'name': 'king bulblin',
        'description': 'King Bulblin 1 fight',
        'filename': 'kb1',
    },
    {
        'name': 'eldin twilight',
        'description': 'Eldin Twilight tears',
        'filename': 'eldin_twilight',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (455.088379, -150.0, 11516.7227),
        'angle': 6058,
        'cam': {
            'center': (219.367218, -20.1253014, 11157.582),
            'eye': (482.515137, -39.9999771, 11558.5283)
        },
    },
    {
        'name': 'forest temple',
        'description': 'Forest Temple segment',
        'filename': 'forest',
    },
    {
        'name': 'diababa',
        'description': 'Forest Temple boss',
        'filename': 'diababa',
    },
    {
        'name': 'pillar clip',
        'description': 'Pillar Clip in Lake Hylia (low water)',
        'filename': 'pillar_clip',
    },
    {
        'name': 'lakebed 1',
        'description': 'The 1st Lakebed Temple segment',
        'filename': 'lakebed1',
    },
    {
        'name': 'deku toad',
        'description': 'Lakebed Temple miniboss',
        'filename': 'deku_toad',
    },
    {
        'name': 'lanayru twilight',
        'description': 'Lanayru Twilight tears',
        'filename': 'lanayru_twilight',
    },
    {
        'name': 'mountain umd',
        'description': 'Snowpeak Mountain w/ UMD',
        'filename': 'mountain_umd',
    },
    {
        'name': 'snowpeak',
        'description': 'The Snowpeak Ruins segment',
        'filename': 'spr',
    },
    {
        'name': 'spr bk room',
        'description': 'Snowpeak Boss Key room',
        'filename': 'spr_bk_room',
    },
    {
        'name': 'blizzeta',
        'description': 'Snowpeak Ruins boss',
        'filename': 'blizzeta',
    },
    {
        'name': 'rusl td',
        'description': 'Text Displacement with Rusl',
        'filename': 'rusl_td',
    },
    {
        'name': 'early ele',
        'description': 'OoB LJA to Death Mountain Elevator',
        'filename': 'early_elavator',
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
        'name': 'lakebed bk skip',
        'description': 'Boss Key skip in Lakebed Temple',
        'filename': 'bk_skip',
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
        'description': 'Morpheel fight (no Zora Armor)',
        'filename': 'morpheel',
        'setflags': SetFlags.POS,
        'pos': (-1193.0, -23999.00, -770.0),
        'angle': 10754,
    },
    {
        'name': 'mdh',
        'description': 'Midna\'s Desperate Hour segment',
        'filename': 'mdh',
    },
    {
        'name': 'bulblin camp',
        'description': 'Bulblin camp segment',
        'filename': 'camp',
    },
    {
        'name': 'arbiter\'s grounds',
        'description': 'The Arbiter\'s Grounds segment',
        'filename': 'ag',
    },
    {
        'name': 'poe gate clip',
        'description': 'Clip through Arbiter\'s Poe Gate',
        'filename': 'poe_gate_clip',
        'setflags': SetFlags.POS,
        'pos': (10.0035, -19.5500, -600.5942),
        'angle': 32768,
    },
    {
        'name': 'death sword',
        'description': 'Arbiter\'s Grounds miniboss',
        'filename': 'deathsword',
    },
    {
        'name': 'stallord',
        'description': 'Arbiter\'s Grounds boss',
        'filename': 'stallord',
    },
    {
        'name': 'faron bomb boost',
        'description': 'Bomb boost to Sacred Grove',
        'filename': 'faron_boost',
    },
    {
        'name': 'temple of time',
        'description': 'The Temple of Time segment',
        'filename': 'tot',
    },
    {
        'name': 'dot skip',
        'description': 'Door of Time skip',
        'filename': 'dot_skip',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (1361.68408, -143.56076, -1089.4801),
        'angle': 33673,
        'cam': {
            'center': (1396.36316, 9.51973343, -719.644531),
            'eye': (1361.59766, -33.1954155, -1090.47632)
        },
    },
    {
        'name': 'silver rupee',
        'description': 'Silver Rupee collection',
        'filename': 'silver_rupee',
    },
    {
        'name': 'city 1',
        'description': 'The 1st City in the Sky segment',
        'filename': 'city1',
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
        'description': 'City in the Sky miniboss',
        'filename': 'aeralfos',
    },
    {
        'name': 'city 2',
        'description': 'The 2nd City in the Sky segment',
        'filename': 'city2',
    },
    {
        'name': 'argorok',
        'description': 'City in the Sky boss',
        'filename': 'argorok',
    },
    {
        'name': 'palace 1',
        'description': 'The 1st Palace of Twilight segment',
        'filename': 'palace1',
    },
    {
        'name': 'palace 2',
        'description': 'The 2nd Palace of Twilight segment',
        'filename': 'palace2',
    },
    {
        'name': 'zant',
        'description': 'Palace of Twilight boss',
        'filename': 'zant',
    },
    {
        'name': 'hyrule castle',
        'description': 'The Hyrule Castle segment',
        'filename': 'hc',
    },
    {
        'name': 'beast ganon',
        'description': 'The Beast Ganon fight',
        'filename': 'beast_ganon',
    },
    {
        'name': 'horseback ganon',
        'description': 'The Horseback Ganondorf fight',
        'filename': 'horseback',
    },
]

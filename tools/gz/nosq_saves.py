from enum import IntEnum

class SetFlags(IntEnum):
    POS = 1
    CAM = 2

NOSQ_SAVES = [
    {
        'name': 'bokoblin push',
        'description': 'Push Bokoblins to Trill',
        'filename': 'boko_push',
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
        'description': 'Faron Twilight segment',
        'filename': 'faron_twilight',
    },
    {
        'name': 'forest temple',
        'description': 'The Forest Temple segment',
        'filename': 'forest_temple',
    },
    {
        'name': 'early boomerang',
        'description': 'Bridge clips to get boomerang early',
        'filename': 'early_rang',
        'setflags': SetFlags.POS,
        'pos': (-2999.1252, 4301.7441, 5233.8784),
        'angle': 32713,
    },
    {
        'name': 'forest escape',
        'description': 'LJA over S.Faron exit trigger',
        'filename': 'forest_escape',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (-12433.6016, -235.969193, -17103.998),
        'angle': 29553,
        'cam': {
            'center': (-12552.8252, -53.5801048, -16729.5313),
            'eye': (-12433.2979, -106.667023, -17104.9512)
        },
    },
    {
        'name': 'gorge void',
        'description': '1 frame jump attack into Gorge',
        'filename': 'gorge_void',
        'setflags': SetFlags.POS,
        'pos': (-9704.47266, -7200.0, 58475.5195),
        'angle': 54288,
    },
    {
        'name': 'rupee roll',
        'description': 'Rupee Roll / Gorge Skip',
        'filename': 'rupee_roll',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (-11130.208, -5700.0, 56423.1953),
        'angle': 31571,
        'cam': {
            'center': (-11178.1504, -5506.71338, 56843.1797),
            'eye': (-11124.4697, -5589.99902, 56373.5195)
        },
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
        'name': 'lanayru twilight',
        'description': 'Lanayru Twilight tears',
        'filename': 'lanayru_twilight',
    },
    {
        'name': 'kb2 skip',
        'description': 'Clip to skip King Bulblin 2',
        'filename': 'kb2_skip',
    },
    {
        'name': 'wagon escort',
        'description': 'Telma wagon escort',
        'filename': 'escort',
    },
    {
        'name': 'pillar clip',
        'description': 'Pillar Clip with Zora Armor',
        'filename': 'pillar_clip',
    },
    {
        'name': 'lakebed',
        'description': 'The Lakebed Temple segment',
        'filename': 'lakebed',
    },
    {
        'name': 'wormhole',
        'description': 'OoB swim to Lakebed east wing',
        'filename': 'wormhole',
    },
    {
        'name': 'lakebed bk skip',
        'description': 'Boss Key skip in Lakebed Temple',
        'filename': 'lakebed_bk_skip',
        'setflags': SetFlags.POS,
        'pos': (2903.0176, -50.0, 1.8442),
        'angle': 49132,
    },
    {
        'name': 'morpheel',
        'description': 'Morpheel fight (Zora Armor)',
        'filename': 'morpheel',
        'setflags': SetFlags.POS,
        'pos': (-1193.0, -23999.00, -770.0),
        'angle': 10754,
    },
    {
        'name': 'messenger skip',
        'description': 'LJA to skip the Snowpeak messengers',
        'filename': 'spr_warp',
        'setflags': SetFlags.POS | SetFlags.CAM,
        'pos': (-9294.87988, 980.0, -11712.3838),
        'angle': 346,
        'cam': {
            'center': (-9309.65137, 1280.4469, -12130.7695),
            'eye': (-9294.2207, 1180.0, -11692.3945)
        },
    },
    {
        'name': 'snowpeak',
        'description': 'The Snowpeak Ruins segment',
        'filename': 'spr',
        'setflags': SetFlags.POS,
        'pos': (0.0, -150.0, 6000.0),
        'angle': 33768,
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
        'filename': 'death_sword',
    },
    {
        'name': 'stallord',
        'description': 'Arbiter\'s Grounds boss',
        'filename': 'stallord',
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
        'description': 'City in the Sky miniboss',
        'filename': 'aeralfos_skip',
    },
    {
        'name': 'city 2',
        'description': 'The 2nd City in the Sky segment',
        'filename': 'cits_2',
    },
    {
        'name': 'argorok',
        'description': 'City in the Sky boss',
        'filename': 'argorok',
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
        'name': 'zant',
        'description': 'Palace of Twilight boss',
        'filename': 'zant',
    },
    {
        'name': 'hyrule castle',
        'description': 'The Hyrule Castle segment',
        'filename': 'hc',
    },
]

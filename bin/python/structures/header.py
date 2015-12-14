from ..defaults.header_guard import __guard__


class Header(object):

    def __init__(self, name):
        self.guard = __guard__.format(GUARD_NAME=name)

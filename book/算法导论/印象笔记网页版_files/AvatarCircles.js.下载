

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','react','classnames','focus-NotesView-NotesList-AvatarCircles-FallbackImg','css!focus/NotesView/NotesList/AvatarCircles/AvatarCircles'],function (require) {
  

  var React = require('react');
  var classnames = require('classnames');

  var FallbackImg = require('focus-NotesView-NotesList-AvatarCircles-FallbackImg');
  require('css!focus/NotesView/NotesList/AvatarCircles/AvatarCircles');

  var BASE_NAME = 'focus-NotesView-NotesList-AvatarCircles-AvatarCircles';

  function prefixedClass(suffix) {
    return BASE_NAME + '-' + suffix;
  }

  /**
   * A row of small avatar circles showing a maximum of three avatars. If more than three
   * avatars are passed, then the right-most circle changes into a label like "+N", where
   * N is the number of avatars that the label replaces.
   */
  var AvatarCircles = React.createClass({
    displayName: 'AvatarCircles',

    propTypes: {
      avatars: React.PropTypes.arrayOf(React.PropTypes.string)
    },

    componentWillMount: function componentWillMount() {
      this.setPreparedAvatars(this.props.avatars);
    },

    componentWillReceiveProps: function componentWillReceiveProps(nextProps) {
      this.setPreparedAvatars(nextProps.avatars);
    },

    getAvatarElements: function getAvatarElements() {
      return this.state.preparedAvatars.map(function (avatar, idx) {
        var containerClasses;
        if (avatar.imgUrl) {
          // Show a user's avatar.
          containerClasses = classnames(prefixedClass('circle'), 'qa-AvatarCircle-face');
          return React.createElement(
            'div',
            { key: 'avatar-' + idx, className: containerClasses },
            React.createElement(FallbackImg, {
              className: prefixedClass('face-image'),
              errorSrc: '/redesign/global/js/focus/img/default_avatar_22x22.png',
              errorSrc2x: '/redesign/global/js/focus/img/default_avatar_22x22@2x.png',
              src: avatar.imgUrl + '?size=22',
              src2x: avatar.imgUrl + '?size=44',
              alt: 'avatar'
            })
          );
        } else if (avatar.groupedCount) {
          // Show an aggregated group count of the remaining avatars.
          containerClasses = classnames(prefixedClass('circle'), prefixedClass('grouped-count'), 'qa-AvatarCircle-count');
          return React.createElement(
            'div',
            { key: 'groupedCount', className: containerClasses },
            '+' + avatar.groupedCount
          );
        } else {
          // Unexpected case; render nothing.
          return null;
        }
      }, this);
    },

    /**
     * Converts a list of avatar URLs into a maximum of three objects. These objects will
     * either have an `imgUrl` field (for displayable avatars) or a `groupedCount` field
     * (for group count labels).
     */
    setPreparedAvatars: function setPreparedAvatars(avatars) {
      function avatarToImgUrlObject(avatar) {
        return {
          imgUrl: avatar
        };
      }

      var preparedAvatars;
      if (!avatars) {
        preparedAvatars = [];
      } else if (avatars.length <= 3) {
        preparedAvatars = avatars.map(avatarToImgUrlObject);
      } else {
        var shownAvatarCount = 2;
        preparedAvatars = avatars.slice(0, shownAvatarCount).map(avatarToImgUrlObject);
        preparedAvatars.push({
          groupedCount: avatars.length - shownAvatarCount
        });
      }

      this.setState({
        preparedAvatars: preparedAvatars
      });
    },

    render: function render() {
      return React.createElement(
        'div',
        null,
        this.getAvatarElements()
      );
    }
  });

  return AvatarCircles;
});
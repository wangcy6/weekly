

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 */
define(['require','react','classnames','resolve!i18n','focus-NotesView-NotesList-AvatarCircles-AvatarCircles','focus-NotesView-NotesList-HoverOptions','css!focus/NotesView/NotesList/Note','focus-NotesView-AutomationTags'],function (require) {
  

  var React = require('react');
  var classnames = require('classnames');
  var i18n = require('resolve!i18n');

  var AvatarCircles = require('focus-NotesView-NotesList-AvatarCircles-AvatarCircles');
  var HoverOptions = require('focus-NotesView-NotesList-HoverOptions');
  require('css!focus/NotesView/NotesList/Note');

  var AUTOMATION_TAGS = require('focus-NotesView-AutomationTags');
  var RESOURCE_THUMBNAIL_SIZE = 96;
  var BASE_NAME = 'focus-NotesView-Note';

  function prefixedClass(suffix) {
    return BASE_NAME + '-' + suffix;
  }

  /**
   * The Note component that is rendered in the NotesList.
   * Gives the user a preview of a note, and which actions they can perform on that note.
   */
  var Note = React.createClass({
    displayName: 'Note',

    propTypes: {
      addShortcut: React.PropTypes.func.isRequired,
      allowsDelete: React.PropTypes.bool,
      allowsExpunge: React.PropTypes.bool,
      allowsReminder: React.PropTypes.bool,
      allowsRestore: React.PropTypes.bool,
      allowsShare: React.PropTypes.bool,
      allowsShortcut: React.PropTypes.bool,
      date: React.PropTypes.string,
      expunge: React.PropTypes.func.isRequired,
      guid: React.PropTypes.string,
      hasReminder: React.PropTypes.bool,
      hasShortcut: React.PropTypes.bool,
      inTrash: React.PropTypes.bool,
      index: React.PropTypes.number,
      isShowDivider: React.PropTypes.bool.isRequired,
      isShowImages: React.PropTypes.bool.isRequired,
      isShowText: React.PropTypes.bool.isRequired,
      isTransitionDisabled: React.PropTypes.bool,
      presentAvatarUrls: React.PropTypes.arrayOf(React.PropTypes.string).isRequired,
      remove: React.PropTypes.func.isRequired,
      removeShortcut: React.PropTypes.func.isRequired,
      restore: React.PropTypes.func.isRequired,
      select: React.PropTypes.func.isRequired,
      selected: React.PropTypes.bool,
      showReminderSetDialog: React.PropTypes.func.isRequired,
      snippet: React.PropTypes.string,
      thumbnailUrl: React.PropTypes.string,
      title: React.PropTypes.string
    },

    getDefaultProps: function getDefaultProps() {
      return {
        presentAvatarUrls: []
      };
    },

    onClick: function onClick() {
      if (this.props.guid) {
        this.props.select(this.props.guid, this.props.index);
      }
    },

    render: function render() {
      var noteTitle = this.props.title || i18n.L('Focus.notesView.loading');
      var classMap = {};
      classMap[prefixedClass('noTransition')] = this.props.isTransitionDisabled;
      classMap[prefixedClass('selected')] = this.props.selected;
      classMap[prefixedClass('hasThumbnail')] = this.props.thumbnailUrl;
      classMap[prefixedClass('noImagesOrText')] = !this.props.isShowText && !this.props.isShowImages;
      classMap[prefixedClass('noImages')] = !this.props.isShowImages && this.props.isShowText;
      classMap[prefixedClass('hasImagesAndText')] = this.props.isShowImages && this.props.isShowText;
      classMap[prefixedClass('hasPresentAvatars')] = this.props.presentAvatarUrls.length;
      var topClasses = classnames(BASE_NAME, classMap);

      var thumbnail;
      if (this.props.isShowImages && this.props.thumbnailUrl) {
        thumbnail = React.createElement('img', {
          className: prefixedClass('snippetThumbnail'),
          src: this.props.thumbnailUrl + '?size=' + RESOURCE_THUMBNAIL_SIZE
        });
      }

      var snippetClasses = classnames(prefixedClass('snippet'), AUTOMATION_TAGS.NOTE_SNIPPET);
      var titleClasses = classnames(prefixedClass('noteTitle'), AUTOMATION_TAGS.NOTE_TITLE);
      var dateClasses = classnames(prefixedClass('date'), AUTOMATION_TAGS.NOTE_DATE);

      var snippet;
      if (this.props.isShowText) {
        snippet = React.createElement(
          'div',
          { className: snippetClasses },
          this.props.snippet
        );
      }

      var divider;
      if (this.props.isShowDivider) {
        divider = React.createElement('div', { className: prefixedClass('snippetDivider') });
      }

      var hoverOptions;
      if (this.props.guid) {
        hoverOptions = React.createElement(HoverOptions, this.props);
      }

      return React.createElement(
        'div',
        { className: topClasses, onClick: this.onClick },
        React.createElement(
          'div',
          { className: prefixedClass('innerSnippetContainer') },
          thumbnail,
          React.createElement('div', { className: prefixedClass('hoverOverlay') }),
          React.createElement('div', { className: prefixedClass('selectOverlay') }),
          React.createElement(
            'div',
            { className: prefixedClass('snippetContent') },
            React.createElement(
              'div',
              { className: titleClasses },
              noteTitle
            ),
            React.createElement(
              'div',
              { className: dateClasses },
              this.props.date
            ),
            snippet
          ),
          React.createElement(
            'div',
            { className: prefixedClass('avatars') },
            React.createElement(AvatarCircles, { avatars: this.props.presentAvatarUrls })
          ),
          divider,
          React.createElement(
            'div',
            { className: prefixedClass('snippetHoverContainer') },
            hoverOptions
          )
        )
      );
    }
  });

  return Note;
});